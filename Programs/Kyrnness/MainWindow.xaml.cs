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
using static Kyrnness.MainWindow;
using static System.Net.Mime.MediaTypeNames;
using static System.Net.WebRequestMethods;

namespace Kyrnness
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static string PathEngine = "F:\\Development\\usengine\\Engine\\Usen";
        public ClassObject SeleactedClass = new ClassObject();

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
            if (parent == null)
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

        private void HppFlagsChanged_CheckedChanged(object sender, RoutedEventArgs e)
        {
            if (hppViewer == null)
                return;

            hppViewer.SelectedClassObject = SeleactedClass;
            hppViewer.UpdateHppFile();
        }

        private void ucFolderHierarchy_ClassSelected(ClassObject SeleactedClass)
        {
            this.SeleactedClass = SeleactedClass;
            hppViewer.SelectedClassObject = SeleactedClass;
            hppViewer.UpdateHppFile();
        }

        //private void UpdateHppFile()
        //{
        //    if (rtbHpp == null)
        //        return;

        //    FlowDocument flowDocument = new FlowDocument();
        //    Paragraph paragraph = new Paragraph();
        //    if (chkIncludePragmaOnce.IsChecked.Value)
        //    {
        //        paragraph.AddTextColor(TColor.TC_Gray, "#pragma once");
        //        paragraph.NewLine();
        //        paragraph.NewLine();
        //    }

        //    if (SeleactedClass != null)
        //    {
        //        AddCopyright(ref paragraph);

        //        AddClassDefineInit(ref paragraph);

        //        AddIncludes(ref paragraph);

        //        AddClassBody(ref paragraph);

        //        paragraph.NewLine();
        //        paragraph.NewLine();

        //        AddClassDefineEnd(ref paragraph);

        //    }


        //    flowDocument.Blocks.Add(paragraph);

        //    rtbHpp.Document = flowDocument;
        //}

        //private void AddClassDefineEnd(ref Paragraph paragraph)
        //{
        //    if (chkIncludeClassDefine.IsChecked.Value)
        //    {
        //        paragraph.AddTextColor(TColor.TC_Gray, "#endif");
        //        paragraph.AddTextColor(TColor.TC_Comment, $" // !{SeleactedClass.ClassDefinition}");
        //    }
        //}
        //private void AddClassBody(ref Paragraph paragraph)
        //{
        //    paragraph.NewLine();
        //    paragraph.AddTextColor(TColor.TC_Directive, "class");
        //    paragraph.AddTextColor(TColor.TC_Object, $" {SeleactedClass.ClassObjectName}");
        //    paragraph.NewLine(TColor.TC_None, text: "{");

        //    AddGeneratedBody(ref paragraph);

        //    paragraph.NewLine(TColor.TC_None, text: "};");
        //}
        //private void AddClassDefineInit(ref Paragraph paragraph)
        //{
        //    if (chkIncludeClassDefine.IsChecked.Value)
        //    {
        //        paragraph.AddTextColor(TColor.TC_Gray, "#ifndef");
        //        paragraph.AddTextColor(TColor.TC_None, $" {SeleactedClass.ClassDefinition}\n");
        //        paragraph.AddTextColor(TColor.TC_Gray, "#define");
        //        paragraph.AddTextColor(TColor.TC_Macro, $" {SeleactedClass.ClassDefinition}\n");

        //        paragraph.NewLine();
        //    }
        //}
        //private void AddIncludes(ref Paragraph paragraph)
        //{
        //    if (chkIncludeGeneratedBody.IsChecked.Value)
        //    {
        //        paragraph.AddTextColor(TColor.TC_Gray, "#include");
        //        paragraph.AddTextColor(TColor.TC_String, $" \"{SeleactedClass.GenneratedHppFileName}\"");
        //        paragraph.NewLine();
        //    }
        //}
        //private void AddGeneratedBody(ref Paragraph paragraph)
        //{
        //    if (chkIncludeGeneratedBody.IsChecked.Value)
        //    {
        //        paragraph.AddTextColor(TColor.TC_Macro, "\n\tDEFAULT_BODY_GENERATED");
        //        paragraph.AddTextColor(TColor.TC_None, "()");
        //        paragraph.NewLine();
        //    }

        //    paragraph.NewLine();
        //    paragraph.AddTextColor(TColor.TC_Directive, "public");
        //    paragraph.AddTextColor(TColor.TC_None, ":");
        //    paragraph.NewLine();
        //}
        //private void AddCopyright(ref Paragraph paragraph)
        //{
        //    if (chkIncludeCopyright.IsChecked.Value)
        //        paragraph.AddTextColor(TColor.TC_Comment, CreateCopyright(SeleactedClass));
        //}

        //        private string CreateCopyright(ClassObject seleactedClass)
        //        {
        //            return $@"/*********************************************************************
        // *   File: {seleactedClass.HppFileName}
        // *  Brief: 
        // * 
        // * Author: Kleyton Lopes
        // *   Date: July 2023
        // * 
        // * Copyright (c) 2023 Kyrnness. All rights reserved. 
        // *********************************************************************/

        //";
        //        }

        //private void ucFolderHierarchy_ClassSelected(ClassObject SeleactedClass)
        //{
        //    this.SeleactedClass = SeleactedClass;
        //    UpdateHppFile();
        //}

    }
    public enum TColor
    {
        TC_None,
        TC_Comment,
        TC_String,
        TC_Object,
        TC_Function,
        TC_Macro,
        TC_Directive,
        TC_Gray
    }
    public static class Extensions
    {
        private static Color ColorGray = Color.FromRgb(128, 128, 128);
        private static Color ColorComment = Color.FromRgb(0, 153, 0);
        private static Color ColorMacro = Color.FromRgb(204, 153, 255);
        private static Color ColorWhite = Color.FromRgb(255, 255, 255);
        private static Color ColorDirective = Color.FromRgb(0, 102, 204);
        private static Color ColorString = Color.FromRgb(255, 178, 102);
        private static Color ColorObject = Color.FromRgb(0, 255, 128);
        private static Color ColorFunction = Color.FromRgb(255, 229, 204);

        public static void AddTextColor(this Paragraph paragraph, TColor color, string text)
        {
            Brush foreColor = new SolidColorBrush(ColorWhite);
            switch (color)
            {
                case TColor.TC_Comment:
                    foreColor = new SolidColorBrush(ColorComment);
                    break;
                case TColor.TC_String:
                    foreColor = new SolidColorBrush(ColorString);
                    break;
                case TColor.TC_Object:
                    foreColor = new SolidColorBrush(ColorObject);
                    break;
                case TColor.TC_Macro:
                    foreColor = new SolidColorBrush(ColorMacro);
                    break;
                case TColor.TC_Directive:
                    foreColor = new SolidColorBrush(ColorDirective);
                    break;
                case TColor.TC_Gray:
                    foreColor = new SolidColorBrush(ColorGray);
                    break;
                case TColor.TC_Function:
                    foreColor = new SolidColorBrush(ColorFunction);
                    break;
            }

            paragraph.Inlines.Add(new Run(text) { Foreground = foreColor });
        }
        public static void NewLine(this Paragraph paragraph, TColor color = TColor.TC_None, string text = "") 
        {
            paragraph.AddTextColor(color, $"\n{text}");
        }
    }
}
