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
using System.Windows.Shapes;

namespace Kyrnness.Pages
{
    /// <summary>
    /// Interaction logic for winNewClass.xaml
    /// </summary>
    public partial class winNewClass : Window
    {
        public FolderObject folder;
        public bool wasCreated = false;
        public ClassObject classObject { get; private set; }

        public winNewClass()
        {
            InitializeComponent();
        }

        private void btnCancel_Click(object sender, RoutedEventArgs e)
        {
            Close();
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
            if (rbClassPrefixF.IsChecked == true)
                return "F";
            if (rbClassPrefixI.IsChecked == true)
                return "I";
            if (rbClassPrefixA.IsChecked == true)
                return "A";
            if (rbClassPrefixB.IsChecked == true)
                return "B";

            return string.Empty;
        }

        private void btnGenerate_Click(object sender, RoutedEventArgs e)
        {
            classObject = new ClassObject();   
            classObject.Name = txtClassName.Text;
            classObject.Folder = folder;
            classObject.Prefix = GetClassPrefix();

            string include = classObject.IncludePath;

            wasCreated = true;
            Close();
        }
    }
}
