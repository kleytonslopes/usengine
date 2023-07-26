using Kyrnness.Data;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
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
using static System.Net.WebRequestMethods;

namespace Kyrnness
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static string PathEngine = "F:\\Development\\usengine\\Engine\\Usen";

        public MainWindow()
        {
            InitializeComponent();
        }

        void LoadFolderStructure()
        {
            string[] directories = Directory.GetDirectories(PathEngine);

            List<FolderObject> folders = new List<FolderObject>();

            foreach (string directory in directories)
            {
                FolderObject folderObject = new FolderObject(NormalizePathName(directory), directory, null);
                folderObject.SubFolders = LoadSubDirectories(folderObject);
                folderObject.Files = LoadSubFiles(folderObject);

                folders.Add(folderObject);
            }

            ucFolderHierarchy.UpdateItemList(folders);
        }

        private List<FileObject> LoadSubFiles(FolderObject folderObject)
        {
            string[] filesPath = Directory.GetFiles(folderObject.FullPath);

            List<FileObject> fileObjects = new List<FileObject>();
            foreach (string filePath in filesPath)
            {
                FileObject file = new FileObject(filePath, folderObject);

                fileObjects.Add(file);
            }
            return fileObjects;
        }

        private string NormalizePathName(string fullPath, FolderObject parent = null)
        {
            if(parent == null)
                return fullPath.Replace($"{PathEngine}\\", "");
            else
                return fullPath.Replace($"{parent.FullPath}\\", "");
        }

        private List<FolderObject> LoadSubDirectories(FolderObject folder)
        {
            string[] directories = Directory.GetDirectories(folder.FullPath);

            List<FolderObject> folders = new List<FolderObject>();

            foreach (string subDirectory in directories)
            {
                FolderObject folderObject = new FolderObject(NormalizePathName(subDirectory, folder), subDirectory, folder);
                folderObject.SubFolders = LoadSubDirectories(folderObject);
                folderObject.Files = LoadSubFiles(folderObject);

                folders.Add(folderObject);
            }

            return folders;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            LoadFolderStructure();
        }

        private void ucFolderHierarchy_FolderStructureChanged()
        {
            LoadFolderStructure();
        }
    }
}
