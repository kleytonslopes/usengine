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
using System.Windows.Shapes;

namespace Kyrnness.Pages
{
    /// <summary>
    /// Interaction logic for winNewFolder.xaml
    /// </summary>
    public partial class winNewFolder : Window
    {
        public FolderObject folderObject;

        public bool wasCreated = false;

        public winNewFolder()
        {
            InitializeComponent();
        }

        private void btnOk_Click(object sender, RoutedEventArgs e)
        {
            string finalPathIncludeFolder = folderObject.FullPath.Replace("src", "include") + "\\" + txtFolderName.Text.Trim().Replace(" ", "");
            string finalPathSourceFolder = folderObject.FullPath.Replace("include", "src") + "\\" + txtFolderName.Text.Trim().Replace(" ", "");
            
            if (!Directory.Exists(finalPathIncludeFolder))
            {
                Directory.CreateDirectory(finalPathIncludeFolder);
                wasCreated = true;
            }
            if (!Directory.Exists(finalPathSourceFolder))
            {
                Directory.CreateDirectory(finalPathSourceFolder);
                wasCreated = true;
            }

            Close();
        }

        private void btnCancel_Click(object sender, RoutedEventArgs e)
        {
            wasCreated = false;
            Close();
        }
    }
}
