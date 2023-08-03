using Kyrnness.Data;
using System;
using System.Collections.Generic;
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
using System.Xml.Linq;
using Kyrnness.Pages;
using System.IO;

namespace Kyrnness.Components
{
    /// <summary>
    /// Interaction logic for ucHierarchyFolder.xaml
    /// </summary>
    public partial class ucHierarchyFolder : UserControl
    {
        public delegate void FolderStructureChangedEventHandler();
        public event FolderStructureChangedEventHandler FolderStructureChanged;

        public delegate void ClassSelectedChangedEvent(ClassObject SeleactedClass);
        public event ClassSelectedChangedEvent ClassSelected;

        public ucHierarchyFolder()
        {
            InitializeComponent();
        }

        public void UpdateItemList(List<FolderObject> folders)
        {
            tvHierarchy.Items.Clear();

            foreach (FolderObject folder in folders)
            {
                TreeViewItem node = new TreeViewItem();
                node.Tag = folder;
                node.Header = folder.Name;

                HierarchyAddChilds(folder, ref node);
                //HierarchyAddFileChilds(folder, ref node);

                tvHierarchy.Items.Add(node);
            }
        }
        private void HierarchyAddChilds(FolderObject folder, ref TreeViewItem node)
        {
            foreach (FolderObject sub in folder.SubFolders)
            {
                TreeViewItem subNode = new TreeViewItem();
                subNode.Tag = sub;
                subNode.Header = sub.Name;

                HierarchyAddChilds(sub, ref subNode);
                //HierarchyAddFileChilds(sub, ref subNode);

                node.Items.Add(subNode);
            }
        }

        private void HierarchyAddFileChilds(FolderObject folder, ref TreeViewItem node)
        {
            if (folder.Files == null)
                return;

            foreach (FileObject file in folder.Files)
            {
                TreeViewItem subNode = new TreeViewItem();
                subNode.Tag = file;
                subNode.Header = file.Name;
                //subNode.Foreground = new SolidColorBrush(Color.FromArgb(255, 160, 160, 160));

                node.Items.Add(subNode);
                //if (file.Extension == "hpp" && !file.IsGenerated)
                //    files.Add(file);
            }
        }

        private void mnuAddFolder_Click(object sender, RoutedEventArgs e)
        {
            TreeViewItem item = tvHierarchy.SelectedItem as TreeViewItem;
            FolderObject folderObject = item.Tag as FolderObject;

            if (folderObject != null)
            {
                winNewFolder wind = new winNewFolder();
                wind.folderObject = folderObject;
                wind.ShowDialog();

                if (wind.wasCreated && FolderStructureChanged != null)
                    FolderStructureChanged();
            }
        }

        private void tvHierarchy_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            tvHierarchy.ContextMenu = tvHierarchy.Resources["SolutionContext"] as System.Windows.Controls.ContextMenu;
        }

        private void mnuRemoveFolder_Click(object sender, RoutedEventArgs e)
        {
            TreeViewItem item = tvHierarchy.SelectedItem as TreeViewItem;
            FolderObject folderObject = item.Tag as FolderObject;

            if (folderObject != null)
            {
                MessageBoxResult result = MessageBox.Show($"Want delete this Folder \"{folderObject.Name}\"?", "Folder - Exclusion", MessageBoxButton.YesNo, MessageBoxImage.Question);
                if (result == MessageBoxResult.Yes)
                {
                    result = MessageBox.Show($"Sure?", "Folder - Exclusion", MessageBoxButton.YesNo, MessageBoxImage.Question);
                    if (result == MessageBoxResult.Yes)
                    {
                        string folderInclude = folderObject.FullPath.Replace("src", "include");
                        string folderSrc = folderObject.FullPath.Replace("include", "src");

                        Directory.Delete(folderInclude, true);
                        Directory.Delete(folderSrc, true);

                        if (FolderStructureChanged != null)
                            FolderStructureChanged();
                    }
                }
            }
        }

        private void mnuAddClass_Click(object sender, RoutedEventArgs e)
        {
            TreeViewItem item = tvHierarchy.SelectedItem as TreeViewItem;
            FolderObject folderObject = item.Tag as FolderObject;
            if (folderObject != null)
            {

                winNewClass wind = new winNewClass();
                wind.folder = folderObject;
                wind.ShowDialog();

                if(wind.wasCreated && ClassSelected != null)
                {
                    ClassSelected(wind.classObject);
                }
            }
        }
    }
}
