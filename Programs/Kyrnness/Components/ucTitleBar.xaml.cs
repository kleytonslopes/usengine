using Kyrnness.Pages;
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

namespace Kyrnness.Components
{
    /// <summary>
    /// Interaction logic for ucTitleBar.xaml
    /// </summary>
    public partial class ucTitleBar : UserControl
    {
        public static readonly DependencyProperty TitleProperty = DependencyProperty.Register(nameof(Title), typeof(string), typeof(ucTitleBar), new PropertyMetadata(string.Empty));

        public string Title
        {
            get 
            { 
                return (string)GetValue(TitleProperty); 
            }
            set
            {
                SetValue(TitleProperty, value);
            }
        }

        public ucTitleBar()
        {
            InitializeComponent();
        }

        private void btnClose_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void btnMaxmize_Click(object sender, RoutedEventArgs e)
        {
            Window window = Window.GetWindow(this);

            window.WindowState = WindowState.Maximized;
            window.WindowStyle = WindowStyle.SingleBorderWindow;
        }

        private void btnMinimize_Click(object sender, RoutedEventArgs e)
        {
            Window window = Window.GetWindow(this);

            window.WindowState = WindowState.Minimized;
           
        }

        private void btnFullscreen_Click(object sender, RoutedEventArgs e)
        {
            Window window = Window.GetWindow(this);

            window.WindowState = WindowState.Maximized;
            window.WindowStyle = WindowStyle.None;
        }

        private void mnuNewClass_Click(object sender, RoutedEventArgs e)
        {
            winNewClass winNewClass = new winNewClass();
            winNewClass.ShowDialog();
        }

        private void UserControl_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
                Window window = Window.GetWindow(this);
                window.DragMove();
        }

    }
}
