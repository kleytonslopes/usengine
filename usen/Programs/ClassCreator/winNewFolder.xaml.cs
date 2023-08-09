using ClassCreator.Data;
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

namespace ClassCreator
{
    /// <summary>
    /// Interaction logic for winNewFolder.xaml
    /// </summary>
    public partial class winNewFolder : Window
    {
        public Dir dir;
        public bool wasCreated = false;
        public winNewFolder()
        {
            InitializeComponent();
        
        }

        private void btnGenerate_Click(object sender, RoutedEventArgs e)
        {
            
            string finalPathIncludeFolder = dir.FullName + "\\" + txtFolderName.Text.Trim();
            string finalPathSourceFolder = dir.FullName.Replace("include", "src") + "\\" + txtFolderName.Text.Trim();
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
            Close();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            lblFolderRoot.Content = dir.PathSource.Replace(dir.Root + "\\", "");
        }
    }
}
