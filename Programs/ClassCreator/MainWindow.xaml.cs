using ClassCreator.Data;
using ClassCreator.Templates;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace ClassCreator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static string EngineFolder = "Engine\\Usen";
        private static string RegClassData = "Config\\class_register.usregcls";
        private static string GenerateBat = "GenerateProjectFile.bat";///"F:\\Development\\usengine\\GenerateProjectFile.bat";

        List<Dir> directoriesHierarchy = new List<Dir>();
        List<Dir> directories = new List<Dir>();
        List<FileDescriptor> files = new List<FileDescriptor>();
        List<ClassRegister> classRegisters = new List<ClassRegister>();


        public MainWindow()
        {
            InitializeComponent();
        }

        private void btnCancel_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void txtClassName_TextChanged(object sender, TextChangedEventArgs e)
        {
            UpdateClassNames();
        }

        private void UpdateClassNames()
        {
            txtClassHeader.Text = $"{txtClassName.Text}.hpp";
            txtClassSource.Text = $"{txtClassName.Text}.cpp";
            lblClassName.Content = $"{GetClassPrefix()}{txtClassName.Text}";

            if (string.IsNullOrEmpty(txtClassName.Text))
            {
                txtClassHeader.Text = string.Empty;
                txtClassSource.Text = string.Empty;
                lblClassName.Content = string.Empty;
            }
        }

        private string GetClassPrefix()
        {
            if (rbClassPrefixU.IsChecked == true)
                return "U";
            if (rbClassPrefixI.IsChecked == true)
                return "I";
            if (rbClassPrefixA.IsChecked == true)
                return "A";
            if (rbClassPrefixB.IsChecked == true)
                return "B";

            return string.Empty;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            try
            {

            
            Reload();
            }
            catch (Exception)
            {

                MessageBox.Show("Error");
            }
        }

        private void Reload()
        {
            directoriesHierarchy = new List<Dir>();
            directories = new List<Dir>();
            files = new List<FileDescriptor>();
            classRegisters = new List<ClassRegister>();

            LoadRegisterClassData();
            LoadClassesData();
            UpdateHierarchyView();
            LoadClassesBase();
        }

        private void LoadClassesBase()
        {
            cboClassBase.Items.Clear();

            if (!classRegisters.Any())
                return;

            foreach (ClassRegister item in classRegisters)
            {
                ListBoxItem lbi = new ListBoxItem();
                lbi.Content = item.ClassName;
                lbi.Tag = item;

                cboClassBase.Items.Add(lbi);
            }
        }

        private void UpdateHierarchyView()
        {
            tvHierarchy.Items.Clear();

            foreach (Dir dir in directoriesHierarchy)
            {
                TreeViewItem node = new TreeViewItem();
                node.Tag = dir;
                node.Header = dir.Name;
                HierarchyAddChilds(dir, ref node);
                HierarchyAddFileChilds(dir, ref node);
                tvHierarchy.Items.Add(node);
            }
        }

        private void HierarchyAddFileChilds(Dir dir, ref TreeViewItem node)
        {
            foreach (FileDescriptor file in dir.Files)
            {
                TreeViewItem subNode = new TreeViewItem();
                subNode.Tag = file;
                subNode.Header = file.Name;
                subNode.Foreground = new SolidColorBrush(Color.FromArgb(255, 160, 160, 160));

                node.Items.Add(subNode);
                if (file.Extension == "hpp" && !file.IsGenerated)
                    files.Add(file);
            }
        }

        private void HierarchyAddChilds(Dir dir, ref TreeViewItem node)
        {
            foreach (Dir sub in dir.Subs)
            {
                TreeViewItem subNode = new TreeViewItem();
                subNode.Tag = sub;
                subNode.Header = sub.Name;
                subNode.Foreground = new SolidColorBrush(Color.FromArgb(255, 0, 102, 204));

                HierarchyAddChilds(sub, ref subNode);
                HierarchyAddFileChilds(sub, ref subNode);

                node.Items.Add(subNode);
            }
        }

        private void LoadClassesData()
        {
            string[] dirs = Directory.GetDirectories(EngineFolder);

            for (int i = 0; i < dirs.Length; i++)
            {
                Dir dir = new Dir(EngineFolder, dirs[i], null);

                dir.Subs = LoadSubFolder(dir);
                dir.Files = LoadFiles(dir);

                directoriesHierarchy.Add(dir);
                directories.Add(dir);
            }
        }

        private List<FileDescriptor> LoadFiles(Dir dir)
        {
            string[] filesPath = Directory.GetFiles(dir.FullName);
            List<FileDescriptor> files = new List<FileDescriptor>();
            for (int i = 0; i < filesPath.Length; i++)
            {
                FileDescriptor file = new FileDescriptor(dir, filesPath[i]);

                files.Add(file);
            }

            return files;
        }

        private List<Dir> LoadSubFolder(Dir dir)
        {
            string[] dirs = Directory.GetDirectories(dir.FullName);
            List<Dir> subs = new List<Dir>();

            for (int i = 0; i < dirs.Length; i++)
            {
                Dir subDir = new Dir(dir.FullName, dirs[i], dir);

                subDir.Subs = LoadSubFolder(subDir);
                subDir.Files = LoadFiles(subDir);

                subs.Add(subDir);
                directories.Add(subDir);
            }

            return subs;
        }

        private void rbClassPrefix_Checked(object sender, RoutedEventArgs e)
        {
            UpdateClassNames();
        }

        private void btnGenerate_Click(object sender, RoutedEventArgs e)
        {
            TreeViewItem selectedItem = tvHierarchy.SelectedItem as TreeViewItem;

            Dir dir = selectedItem?.Tag as Dir;

            if (selectedItem == null || dir == null)
            {
                MessageBox.Show("Path not selected!", "Information", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            ClassData classData = MakeClassData();
            BuildTemplate buildTemplate = new BuildTemplate();
            string cpp = buildTemplate.GenerateClassCpp(classData);
            string hpp = buildTemplate.GenerateClassHpp(classData);
            string gen = buildTemplate.GenerateClassGen(classData);

            string fileCpp = $"{EngineFolder}\\{classData.FolderCpp.Replace("/", "\\")}\\{classData.CppFileName}";
            string fileHpp = $"{EngineFolder}\\{classData.FolderHpp.Replace("/", "\\")}\\{classData.HppFileName}";
            string fileGen = $"{EngineFolder}\\{classData.FolderGen.Replace("/", "\\")}\\{classData.GenFileName}";

            File.WriteAllText($"{fileCpp}", cpp);
            File.WriteAllText($"{fileHpp}", hpp);
            File.WriteAllText($"{fileGen}", gen);

            SaveRegisterClass(classData);
        }

        private ClassData MakeClassData()
        {
            ClassData classData = new ClassData();
            classData.ClassName = GetClassName();
            classData.ClassDefinition = GetClassDefinition();
            classData.HppFileName = txtClassHeader.Text.Trim();
            classData.CppFileName = txtClassSource.Text.Trim();
            classData.GenFileName = GetGenFileName();
            classData.FolderHpp = GetClassHppFolder();
            classData.FolderCpp = GetClassCppFolder();
            classData.FolderGen = GetClassGenFolder();
            classData.DateCreation = DateTime.Now.ToString("MMMM yyyy", new CultureInfo("en-US"));

            classData.BaseClassName = GetBaseClassName();
            classData.BaseClassPathHpp = GetBaseClassPathHpp();
            classData.BaseClassTemplate = GetBaseClassTemplate();
            classData.BaseClassInclude = GetBaseClassInclude();

            classData.ClassGenDefinition = GetClassGenDefinition();
            classData.ClassGenDefinitionVersion = GetClassGenDefinitionVersion();

            return classData;
        }

        private string GetBaseClassInclude()
        {
            if (cboClassBase.SelectedIndex < 0)
                return string.Empty;

            return $"\n#include \"{GetBaseClassPathHpp()}\"";
        }

        private string GetBaseClassTemplate()
        {
            if (cboClassBase.SelectedIndex < 0)
                return string.Empty;

            string caps = string.Empty;

            if (cboClassBase.SelectedIndex == 1)
                caps = "protected";
            else if (cboClassBase.SelectedIndex == 2)
                caps = "private";
            else
                caps = "public";

            string classBaseName = GetBaseClassName();

            return $" : {caps} {classBaseName}";
        }

        private string GetClassDefinition()
        {
            string definition = "US_" + Regex.Replace(txtClassName.Text, "([a-z])([A-Z])", "$1 $2") + "_HPP";
            definition = definition.ToUpper().Replace(" ", "_");

            return definition;
        }

        private string GetClassGenDefinitionVersion()
        {
            return $"{GetClassGenDefinition()}_def";
        }

        private string GetClassGenDefinition()
        {
            string classBaseName = GetBaseClassName();

            if (string.IsNullOrWhiteSpace(classBaseName))
                return $"hpp_{GetClassName()}";

            return $"hpp_{GetClassName()}_{classBaseName}";
        }

        private string GetBaseClassPathHpp()
        {
            if (cboClassBase.SelectedIndex < 0)
                return string.Empty;

            ListBoxItem lib = cboClassBase.SelectedItem as ListBoxItem;

            if(lib == null) return string.Empty;

            ClassRegister classRegister = lib.Tag as ClassRegister;
            if(classRegister == null) return string.Empty;

            return $"{classRegister.Data.FolderHpp.Replace("include/", "")}/{classRegister.Data.HppFileName}";
        }

        private string GetBaseClassName()
        {
            if (cboClassBase.SelectedIndex < 0)
                return string.Empty;

            return cboClassBase.Text;
        }

        private string GetClassGenFolder()
        {
            return "generated";
        }

        private string GetClassCppFolder()
        {
            TreeViewItem selectedItem = tvHierarchy.SelectedItem as TreeViewItem;

            Dir dir = selectedItem.Tag as Dir;

            if (dir != null)
            {
                return "src" + $"/{dir.PathSource}"
                    .Replace("\\", "/")
                    .Replace("include/", "")
                    .Replace("src/", "")
                    .Replace("generated/", "")
                    ;
            }

            return "src";
        }

        private string GetClassHppFolder()
        {
            TreeViewItem selectedItem = tvHierarchy.SelectedItem as TreeViewItem;

            Dir dir = selectedItem.Tag as Dir;

            if (dir != null)
            {
                return "include" + $"/{dir.PathSource}"
                    .Replace("\\", "/")
                    .Replace("include/", "")
                    .Replace("src/", "")
                    .Replace("generated/", "")
                    ;
            }

            return "include";
        }

        private string GetGenFileName()
        {
            return $"{txtClassName.Text.Trim()}-generated.hpp";
        }

        private string GetClassName()
        {
            UpdateClassNames();

            return lblClassName.Content.ToString();
        }

        private void SaveRegisterClass(ClassData classData)
        {
            ClassRegister classRegister = new ClassRegister();
            classRegister.ClassName = classData.ClassName;
            classRegister.Data = classData;

            classRegisters.Add(classRegister);

            string json = JsonConvert.SerializeObject(classRegisters, Formatting.Indented);

            File.WriteAllText(RegClassData, json);

            Reload();
            GenerateProjectFiles();
        }

        private void GenerateProjectFiles()
        {
            System.Diagnostics.Process.Start(GenerateBat);
        }

        private void LoadRegisterClassData()
        {
            string fileBoy = File.ReadAllText(RegClassData);

            if (string.IsNullOrWhiteSpace(fileBoy))
                return;

            classRegisters = JsonConvert.DeserializeObject<List<ClassRegister>>(fileBoy);
        }
    }
}
