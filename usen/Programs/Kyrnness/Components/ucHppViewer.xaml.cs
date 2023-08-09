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

namespace Kyrnness.Components
{
    /// <summary>
    /// Interaction logic for ucHppViewer.xaml
    /// </summary>
    public partial class ucHppViewer : UserControl
    {
        public ClassObject SelectedClassObject { get; set; }
        //public static readonly DependencyProperty ClassObjectProperty = DependencyProperty.Register(nameof(SelectedClassObject), typeof(string), typeof(ucHppViewer), new PropertyMetadata(default(ClassObject)));

        //public ClassObject SelectedClassObject
        //{
        //    get
        //    {
        //        return (ClassObject)GetValue(ClassObjectProperty);
        //    }
        //    set
        //    {
        //        if(value != null) 
        //            SetValue(ClassObjectProperty, value);
        //    }
        //}

        public ucHppViewer()
        {
            InitializeComponent();
        }

        public void UpdateHppFile()
        {
            if (rtbViewer == null || SelectedClassObject == null)
                return;

            FlowDocument flowDocument = new FlowDocument();
            Paragraph paragraph = new Paragraph();
            if (SelectedClassObject.HasPragmaOnce)
            {
                paragraph.AddTextColor(TColor.TC_Gray, "#pragma once");
                paragraph.NewLine();
                paragraph.NewLine();
            }

            if (SelectedClassObject != null)
            {
                AddCopyright(ref paragraph);

                AddClassDefineInit(ref paragraph);

                AddIncludes(ref paragraph);

                AddClassBody(ref paragraph);

                paragraph.NewLine();
                paragraph.NewLine();

                AddClassDefineEnd(ref paragraph);

            }


            flowDocument.Blocks.Add(paragraph);

            rtbViewer.Document = flowDocument;
        }
        private void AddClassDefineEnd(ref Paragraph paragraph)
        {
            if (SelectedClassObject.HasDefinition)
            {
                paragraph.AddTextColor(TColor.TC_Gray, "#endif");
                paragraph.AddTextColor(TColor.TC_Comment, $" // !{SelectedClassObject.ClassDefinition}");
            }
        }
        private void AddClassBody(ref Paragraph paragraph)
        {
            paragraph.NewLine();
            paragraph.AddTextColor(TColor.TC_Directive, "class");
            paragraph.AddTextColor(TColor.TC_Object, $" {SelectedClassObject.ClassObjectName}");
            paragraph.NewLine(TColor.TC_None, text: "{");

            AddGeneratedBody(ref paragraph);

            paragraph.NewLine(TColor.TC_None, text: "};");
        }
        private void AddClassDefineInit(ref Paragraph paragraph)
        {
            if (SelectedClassObject.HasDefinition)
            {
                paragraph.AddTextColor(TColor.TC_Gray, "#ifndef");
                paragraph.AddTextColor(TColor.TC_None, $" {SelectedClassObject.ClassDefinition}\n");
                paragraph.AddTextColor(TColor.TC_Gray, "#define");
                paragraph.AddTextColor(TColor.TC_Macro, $" {SelectedClassObject.ClassDefinition}\n");

                paragraph.NewLine();
            }
        }
        private void AddIncludes(ref Paragraph paragraph)
        {
            if (SelectedClassObject.HasGeneratedBody)
            {
                paragraph.AddTextColor(TColor.TC_Gray, "#include");
                paragraph.AddTextColor(TColor.TC_String, $" \"{SelectedClassObject.GenneratedHppFileName}\"");
                paragraph.NewLine();
            }
        }
        private void AddGeneratedBody(ref Paragraph paragraph)
        {
            if (SelectedClassObject.HasGeneratedBody)
            {
                paragraph.AddTextColor(TColor.TC_Macro, "\n\tDEFAULT_BODY_GENERATED");
                paragraph.AddTextColor(TColor.TC_None, "()");
                paragraph.NewLine();
            }

            paragraph.NewLine();
            paragraph.AddTextColor(TColor.TC_Directive, "public");
            paragraph.AddTextColor(TColor.TC_None, ":");
            paragraph.NewLine();
        }
        private void AddCopyright(ref Paragraph paragraph)
        {
            if (SelectedClassObject.HasCopyright)
                paragraph.AddTextColor(TColor.TC_Comment, CreateCopyright());
        }

        private string CreateCopyright()
        {
            return $@"/*********************************************************************
 *   File: {SelectedClassObject.HppFileName}
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/

";
        }
    }
}
