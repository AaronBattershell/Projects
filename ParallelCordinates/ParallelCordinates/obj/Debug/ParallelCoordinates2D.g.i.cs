﻿#pragma checksum "..\..\ParallelCoordinates2D.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "A38A41D5A08165DEC4114A531B9E0C7C"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.18444
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;


namespace ParallelCordinates {
    
    
    /// <summary>
    /// ParallelCoordinates2D
    /// </summary>
    public partial class ParallelCoordinates2D : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 2 "..\..\ParallelCoordinates2D.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal ParallelCordinates.ParallelCoordinates2D window;
        
        #line default
        #line hidden
        
        
        #line 9 "..\..\ParallelCoordinates2D.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ScrollViewer canvasContainer;
        
        #line default
        #line hidden
        
        
        #line 13 "..\..\ParallelCoordinates2D.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Canvas canvas;
        
        #line default
        #line hidden
        
        
        #line 14 "..\..\ParallelCoordinates2D.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button defaultSettingsBtn;
        
        #line default
        #line hidden
        
        
        #line 19 "..\..\ParallelCoordinates2D.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Border defaultSettingsGrid;
        
        #line default
        #line hidden
        
        
        #line 22 "..\..\ParallelCoordinates2D.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox MinColumnWidthTxtBx;
        
        #line default
        #line hidden
        
        
        #line 27 "..\..\ParallelCoordinates2D.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox BeginNumericAproxTxtBx;
        
        #line default
        #line hidden
        
        
        #line 30 "..\..\ParallelCoordinates2D.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.CheckBox FilterTxtBx;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/ParallelCordinates;component/parallelcoordinates2d.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\ParallelCoordinates2D.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.window = ((ParallelCordinates.ParallelCoordinates2D)(target));
            return;
            case 2:
            this.canvasContainer = ((System.Windows.Controls.ScrollViewer)(target));
            return;
            case 3:
            this.canvas = ((System.Windows.Controls.Canvas)(target));
            
            #line 13 "..\..\ParallelCoordinates2D.xaml"
            this.canvas.MouseDown += new System.Windows.Input.MouseButtonEventHandler(this.mouseDown);
            
            #line default
            #line hidden
            
            #line 13 "..\..\ParallelCoordinates2D.xaml"
            this.canvas.MouseUp += new System.Windows.Input.MouseButtonEventHandler(this.mouseUP);
            
            #line default
            #line hidden
            return;
            case 4:
            this.defaultSettingsBtn = ((System.Windows.Controls.Button)(target));
            
            #line 14 "..\..\ParallelCoordinates2D.xaml"
            this.defaultSettingsBtn.Click += new System.Windows.RoutedEventHandler(this.ShowGridSettings);
            
            #line default
            #line hidden
            return;
            case 5:
            this.defaultSettingsGrid = ((System.Windows.Controls.Border)(target));
            return;
            case 6:
            this.MinColumnWidthTxtBx = ((System.Windows.Controls.TextBox)(target));
            
            #line 22 "..\..\ParallelCoordinates2D.xaml"
            this.MinColumnWidthTxtBx.PreviewTextInput += new System.Windows.Input.TextCompositionEventHandler(this.PreviewTextInput);
            
            #line default
            #line hidden
            
            #line 22 "..\..\ParallelCoordinates2D.xaml"
            this.MinColumnWidthTxtBx.LostFocus += new System.Windows.RoutedEventHandler(this.ValidateCount);
            
            #line default
            #line hidden
            return;
            case 7:
            this.BeginNumericAproxTxtBx = ((System.Windows.Controls.TextBox)(target));
            
            #line 27 "..\..\ParallelCoordinates2D.xaml"
            this.BeginNumericAproxTxtBx.PreviewTextInput += new System.Windows.Input.TextCompositionEventHandler(this.PreviewTextInput);
            
            #line default
            #line hidden
            return;
            case 8:
            this.FilterTxtBx = ((System.Windows.Controls.CheckBox)(target));
            return;
            case 9:
            
            #line 31 "..\..\ParallelCoordinates2D.xaml"
            ((System.Windows.Controls.Button)(target)).Click += new System.Windows.RoutedEventHandler(this.ApplyChanges);
            
            #line default
            #line hidden
            return;
            case 10:
            
            #line 32 "..\..\ParallelCoordinates2D.xaml"
            ((System.Windows.Controls.Button)(target)).Click += new System.Windows.RoutedEventHandler(this.CloseSettingsWindow);
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}

