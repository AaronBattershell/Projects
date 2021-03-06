﻿using System;
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
using System.IO;
using DataReader;

namespace ParallelCordinates
{
    public partial class ParallelCoordinates2D : Window
    {
        double CalculatedXStep;

        double MinXStep;
        int StartApproximation;
        int MaxUniqueEntries;
        bool HideFiltered;

        const double BORDER_DISTANCE = 50;
        const double NUMERIC_POINTS = 5;
        const double Y_COLUMN_OFFSET = - BORDER_DISTANCE / 2;
        const double TEXT_OFFSET_X = 3;
        const double TEXT_OFFSET_Y = - 25;
        const string EMPTY_FIELD = "[Not Available]";

        int DownMouseColumnIndex = -1;
        int UpMouseColumnIndex = -1;

        List<bool> FilteredList;
        //List<DataEntry> OriginalDataList;

        Border settingsGrid;
        Button settingsBtn;
        DisplayData GraphData;

        public ParallelCoordinates2D()
        {
            InitializeComponent();
        }

        public ParallelCoordinates2D(List<DataEntry> userData, int minColumnWidth, int beginNumericAprox, int maxUniqueEntries, bool hideFiltered) : this()
        {
            //OriginalDataList = userData;
            settingsGrid = defaultSettingsGrid;
            settingsBtn = defaultSettingsBtn;

            settingsGrid.Visibility = Visibility.Hidden;

            MinXStep = minColumnWidth;
            StartApproximation = beginNumericAprox;
            MaxUniqueEntries = beginNumericAprox;
            HideFiltered = hideFiltered;

            GraphData = new DisplayData();
            GraphData.GridData = userData.Where(e => e.UniquEntries <= MaxUniqueEntries || e.AllNumbers == true).ToList();

            string[] unusedColumnNames = userData.Where(e => e.UniquEntries > MaxUniqueEntries && e.AllNumbers == false).Select(e => e.ColumnName).ToArray();

            // Alert user of unusable columns
            if (unusedColumnNames.Length > 0)
            {
                string errorMessage = "The following data column" + (unusedColumnNames.Length > 1 ? "s" : "") + " were removed for having too many unique non-numeric entries: ";
                string badColumns = string.Join(", ", unusedColumnNames);

                System.Windows.MessageBox.Show(errorMessage + badColumns, "Invalid Columns", System.Windows.MessageBoxButton.OK);
            }

            FilteredList = new List<bool>(new bool[GraphData.GridData[0].Data.Count]);

            canvas.Height = (int)SystemParameters.FullPrimaryScreenHeight - 17;
            canvas.Width = (int)SystemParameters.FullPrimaryScreenWidth;

            double normalWidth = (canvas.Width - BORDER_DISTANCE * 2) / GraphData.GridData.Count;
            CalculatedXStep = Math.Max(normalWidth, MinXStep);
            canvas.Width = CalculatedXStep * GraphData.GridData.Count + BORDER_DISTANCE * 2;

            // Calculate vertical Lines and text
            for (int i = 0; i < GraphData.GridData.Count; ++i)
            {
                GraphData.ColumnPositions.Add(new ColumnData(new Point(CalculatedXStep * i + CalculatedXStep / 2 + BORDER_DISTANCE, BORDER_DISTANCE - Y_COLUMN_OFFSET), new Point(CalculatedXStep * i + CalculatedXStep / 2 + BORDER_DISTANCE, canvas.Height - BORDER_DISTANCE - Y_COLUMN_OFFSET)));
            }

            // Calculate horizontal Lines
            for (int i = 0; i < GraphData.GridData.Count; ++i)
            {
                if (GraphData.GridData[i].AllNumbers && GraphData.GridData[i].UniquEntries > StartApproximation)
                {
                    for (int j = 0; j < NUMERIC_POINTS; ++j)
                    {
                        double labelNumber = (j == 0 ? GraphData.GridData[i].NumberRange.First : (j == NUMERIC_POINTS - 1 ? GraphData.GridData[i].NumberRange.Second : (GraphData.GridData[i].NumberRange.Second - GraphData.GridData[i].NumberRange.First) * (j / (double)NUMERIC_POINTS) + GraphData.GridData[i].NumberRange.First));

                        GraphData.GridData[i].YPlacements[labelNumber.ToString()] = (int)(j / (NUMERIC_POINTS + (GraphData.GridData[i].ContainsEmptyEntry ? 1 : 0)) * (canvas.Height - 2 * BORDER_DISTANCE) + (0.5 / (NUMERIC_POINTS + (GraphData.GridData[i].ContainsEmptyEntry ? 1 : 0)) * (canvas.Height - 2 * BORDER_DISTANCE)) + BORDER_DISTANCE - Y_COLUMN_OFFSET);
                    }

                    if (GraphData.GridData[i].ContainsEmptyEntry)
                    {
                        GraphData.GridData[i].YPlacements[EMPTY_FIELD] = (int)((NUMERIC_POINTS) / (NUMERIC_POINTS + (GraphData.GridData[i].ContainsEmptyEntry ? 1 : 0)) * (canvas.Height - 2 * BORDER_DISTANCE) + (0.5 / (NUMERIC_POINTS + (GraphData.GridData[i].ContainsEmptyEntry ? 1 : 0)) * (canvas.Height - 2 * BORDER_DISTANCE)) + BORDER_DISTANCE - Y_COLUMN_OFFSET);
                    }
                }
                else
                {
                    var uniquValues = GraphData.GridData[i].Data.Distinct().Where(e => e[0] != '[').ToList();

                    sortList(ref uniquValues, GraphData.GridData[i].AllNumbers);

                    if (GraphData.GridData[i].ContainsEmptyEntry)
                    {
                        uniquValues.Add(EMPTY_FIELD);
                    }

                    for (int j = 0; j < uniquValues.Count; ++j)
                    {
                        GraphData.GridData[i].YPlacements[uniquValues[j]] = ((int)(j / (double)GraphData.GridData[i].UniquEntries * (canvas.Height - 2 * BORDER_DISTANCE) + (0.5 / (double)GraphData.GridData[i].UniquEntries * (canvas.Height - 2 * BORDER_DISTANCE)) + BORDER_DISTANCE - Y_COLUMN_OFFSET));
                    }
                }
            }

            drawScreen();
        }

        public void sortList(ref List<string> values, bool isNumbers = false)
        {
            if (!isNumbers)
            {
                values.Sort();
            }
            else
            {
                List<double> newValues = new List<double>();
                foreach (var val in values)
                {
                    newValues.Add(double.Parse(val));
                }

                newValues.Sort();

                values = new List<string>();

                foreach (var val in newValues)
                {
                    values.Add(val.ToString());
                }
            }
        }

        public Line DrawLine(Pen p, Point p1, Point p2)
        {
            Line l = new Line()
            {
                X1 = p1.X,
                Y1 = p1.Y,
                X2 = p2.X,
                Y2 = p2.Y,
                StrokeThickness = p.Thickness,
                Stroke = p.Brush
            };

            return l;
        }

        public Rectangle DrawRectangle(Point topLeft, Point bottomRight, SolidColorBrush outline, SolidColorBrush fill)
        {
            Rectangle r = new Rectangle()
            {
                Stroke = outline,
                Fill = fill,
                Width = Convert.ToDouble(Math.Abs(bottomRight.X - topLeft.X)),
                Height = Convert.ToDouble(Math.Abs(bottomRight.Y - topLeft.Y)),
                Margin = new Thickness(topLeft.X, topLeft.Y, 0, 0)
            };

            return r;
        }

        public TextBlock DrawText(string text, Point location, Color color)
        {
            TextBlock t = new TextBlock()
            {
                Text = text,
                Foreground = new SolidColorBrush(color),
                Height = 30,
                Width = 200,
                Margin = new Thickness(location.X, location.Y, 0, 0)
            };

            return t;
        }

        private void mouseDown(object sender, RoutedEventArgs e)
        {
            Point downClick = Mouse.GetPosition(canvas);
            DownMouseColumnIndex = getColumn(downClick);

            // Ensure that the column is currently not already selected
            if (GraphData.GridData[DownMouseColumnIndex].DisplayFilter.First == -1)
            {
                GraphData.GridData[DownMouseColumnIndex].DisplayFilter.First = downClick.Y; 
            }
        }

        private void mouseUP(object sender, RoutedEventArgs e)
        {
            // Check for column click
            Point upClick = Mouse.GetPosition(canvas);

            int upMouseColumnClick = getColumn(upClick);
            if (upMouseColumnClick == DownMouseColumnIndex)
            {
                // Add filter for column
                if (GraphData.GridData[upMouseColumnClick].DisplayFilter.Second == -1 && Math.Abs(GraphData.GridData[DownMouseColumnIndex].DisplayFilter.First - upClick.Y) >= 5)
                {
                    // Assign lowest to first, heighest to second
                    GraphData.GridData[upMouseColumnClick].DisplayFilter.Second = Math.Max(upClick.Y, GraphData.GridData[upMouseColumnClick].DisplayFilter.First);
                    GraphData.GridData[upMouseColumnClick].DisplayFilter.First = Math.Min(upClick.Y, GraphData.GridData[upMouseColumnClick].DisplayFilter.First);

                    GraphData.GridData[upMouseColumnClick].Filtered = true;
                }
                else // remove data filter for column
                {
                    GraphData.GridData[upMouseColumnClick].Filtered = false;
                    GraphData.GridData[upMouseColumnClick].DisplayFilter.First = -1;
                    GraphData.GridData[upMouseColumnClick].DisplayFilter.Second = -1;
                }

                // Filter or free constraints based upon restrictions
                setFilters();
                drawScreen();

                return;
            }


            // Check for column drag
            UpMouseColumnIndex = getBetweenColumns(upClick);

            if (UpMouseColumnIndex != -1 && DownMouseColumnIndex != -1 && !(UpMouseColumnIndex - 2 < DownMouseColumnIndex && UpMouseColumnIndex + 1 > DownMouseColumnIndex))
            {
                GraphData.GridData.Last().Data.Last().ToString();
                var dataHolder = GraphData.GridData[DownMouseColumnIndex];

                GraphData.GridData.RemoveAt(DownMouseColumnIndex);

                if (DownMouseColumnIndex < UpMouseColumnIndex)
                {
                    --UpMouseColumnIndex;
                    GraphData.GridData.Insert(UpMouseColumnIndex, dataHolder);
                }
                else
                {
                    GraphData.GridData.Insert(UpMouseColumnIndex, dataHolder);
                }

                drawScreen();
            }

            UpMouseColumnIndex = -1;
        }

        private void setFilters()
        {
            for (int i = 0; i < FilteredList.Count; ++i)
            {
                FilteredList[i] = false;
            }

            for (int i = 0; i < GraphData.GridData.Count; ++i)
            {
                if (GraphData.GridData[i].DisplayFilter.First == -1 && GraphData.GridData[i].DisplayFilter.Second == -1)
                {
                    continue;
                }

                for (int j = 0; j < GraphData.GridData[i].Data.Count; ++j)
                {
                    double comparableValueHeight;

                    // Estimate
                    if (GraphData.GridData[i].AllNumbers && GraphData.GridData[i].UniquEntries > StartApproximation)
                    {
                        comparableValueHeight = getDataPointCoordinates(j, i).Y;
                    }
                    else // Non-estimate
                    {
                        comparableValueHeight = GraphData.GridData[i].YPlacements[GraphData.GridData[i].Data[j]];
                    }

                    if (GraphData.GridData[i].DisplayFilter.First > comparableValueHeight || comparableValueHeight > GraphData.GridData[i].DisplayFilter.Second)
                    {
                        FilteredList[j] = true;
                    }
                }
            }
        }

        public int getColumn(Point p)
        {
            for (int i = 0; i < GraphData.GridData.Count; ++i)
            {
                double halfWidth = CalculatedXStep / 2;

                if (GraphData.ColumnPositions[i].Top.X - halfWidth < p.X && p.X < GraphData.ColumnPositions[i].Top.X + halfWidth)
                {
                    return i;
                }
            }

            return 0;
        }

        // Returns the column index to the right of your cursor
        public int getBetweenColumns(Point p)
        {
            //Special case: first column
            if (p.X < GraphData.ColumnPositions[0].Top.X)
            {
                return 0;
            }

            for (int i = 0; i < GraphData.GridData.Count - 1; ++i)
            {
                if (GraphData.ColumnPositions[i].Top.X < p.X && p.X < GraphData.ColumnPositions[i + 1].Top.X)
                {
                    return i + 1;
                }
            }

            return GraphData.GridData.Count;
        }

        void drawScreen()
        {
            canvas.Children.Clear();

            drawColumns();
            drawDatasetLines();
            drawColumnDataPoints();
            drawSettingsButton();
        }

        void drawColumns()
        {
            for (int i = 0; i < GraphData.GridData.Count; ++i)
            {
                canvas.Children.Add(DrawLine(new Pen(Brushes.DarkGray, 1), GraphData.ColumnPositions[i].Top, GraphData.ColumnPositions[i].Botumn));
                canvas.Children.Add(DrawText(GraphData.GridData[i].ColumnName, new Point(GraphData.ColumnPositions[i].Top.X - GraphData.GridData[i].ColumnName.Length * TEXT_OFFSET_X, -Y_COLUMN_OFFSET / 2 + (CalculatedXStep < 150 ? (i % 3) * 20 : 0)), Colors.Black));

                if (GraphData.GridData[i].Filtered)
                {
                    Point topLeft = new Point(GraphData.ColumnPositions[i].Top.X - Math.Min(30, CalculatedXStep / 3), GraphData.GridData[i].DisplayFilter.First);
                    Point bottomRight = new Point(GraphData.ColumnPositions[i].Botumn.X + Math.Min(30, CalculatedXStep/3), GraphData.GridData[i].DisplayFilter.Second);
                    canvas.Children.Add(DrawRectangle(topLeft, bottomRight, Brushes.Black, Brushes.Transparent));
                }
            }
        }

        void drawColumnDataPoints()
        {
            for (int i = 0; i < GraphData.GridData.Count; ++i)
            {
                foreach (var field in GraphData.GridData[i].YPlacements)
                {
                    canvas.Children.Add(DrawLine(new Pen(Brushes.Black, 2), new Point(GraphData.ColumnPositions[i].Top.X - 10, field.Value), new Point(GraphData.ColumnPositions[i].Top.X + 10, field.Value)));
                    canvas.Children.Add(DrawText(field.Key, new Point(GraphData.ColumnPositions[i].Top.X - field.Key.Length * TEXT_OFFSET_X, field.Value + TEXT_OFFSET_Y), Colors.Black));
                }
            }
        }

        void drawDatasetLines()
        {
            for (int i = 0; i < GraphData.GridData[0].Data.Count; ++i)
            {
                if (!FilteredList[i] || !HideFiltered) 
                {
                    Point left = getDataPointCoordinates(i, 0);
                    Point right;

                    for (int j = 1; j < GraphData.GridData.Count; ++j)
                    {
                        right = getDataPointCoordinates(i, j);

                        canvas.Children.Add(DrawLine(new Pen((FilteredList[i] ? Brushes.LightGray : Brushes.DarkBlue), .5), left, right));
                        left = right;
                    }
                }
            }
        }

        void drawSettingsButton()
        {
            canvas.Children.Add(settingsBtn);
            canvas.Children.Add(settingsGrid);
        }

        Point getDataPointCoordinates(int i, int j)
        {
            // Case: Too many numeric points, so approximation must take place
            if (GraphData.GridData[j].AllNumbers && GraphData.GridData[j].UniquEntries > StartApproximation)
            {
                //  Case: No avalid entry provided
                if (GraphData.GridData[j].Data[i][0] == '[')
                {
                    return new Point(GraphData.ColumnPositions[j].Top.X, GraphData.GridData[j].YPlacements[EMPTY_FIELD]);
                }
                else // Case: Approximate location of numeric point
                {
                    // Point location based on range extreem values
                    double range = (GraphData.GridData[j].NumberRange.Second - GraphData.GridData[j].NumberRange.First);
                    double currentValue = Double.Parse(GraphData.GridData[j].Data[i]);
                    double heightPercentage = (currentValue - GraphData.GridData[j].NumberRange.First) / range;
                    double heightDistance = GraphData.GridData[j].YPlacements[GraphData.GridData[j].NumberRange.Second.ToString()] - GraphData.GridData[j].YPlacements[GraphData.GridData[j].NumberRange.First.ToString()];
                    double YVal = heightPercentage * heightDistance + GraphData.GridData[j].YPlacements[GraphData.GridData[j].NumberRange.First.ToString()];
                    return new Point(GraphData.ColumnPositions[j].Top.X, YVal);
                }
            }
            else // Case: No approximations needed 
            {
                string currentField = (GraphData.GridData[j].Data[i][0] == '[' ? EMPTY_FIELD : GraphData.GridData[j].Data[i]);
                return new Point(GraphData.ColumnPositions[j].Top.X, GraphData.GridData[j].YPlacements[currentField]);
            }
        }

        static void swap<T>(ref T left, ref T right)
        {
            T temp = left;
            left = right;
            right = temp;
        }

        private void CloseSettingsWindow(object sender, RoutedEventArgs e)
        {
            settingsGrid.Visibility = Visibility.Hidden;
        }

        private void ApplyChanges(object sender, RoutedEventArgs e)
        {
            if (MinXStep != Int32.Parse(MinColumnWidthTxtBx.Text) || StartApproximation != Int32.Parse(BeginNumericAproxTxtBx.Text)/* || MaxUniqueEntries != Int32.Parse(MaxUniqueEntriesTxtBx.Text)*/)
            {
                MinXStep = Int32.Parse(MinColumnWidthTxtBx.Text);
                StartApproximation = Int32.Parse(BeginNumericAproxTxtBx.Text);
                //MaxUniqueEntries = Int32.Parse(MaxUniqueEntriesTxtBx.Text);
                
                // START NEW CHANGES
                //GraphData.GridData = OriginalDataList.Where(ee => ee.UniquEntries <= MaxUniqueEntries || ee.AllNumbers == true).ToList();
                FilteredList = new List<bool>(new bool[GraphData.GridData[0].Data.Count]);

                canvas.Width = (int)SystemParameters.FullPrimaryScreenWidth;

                double normalWidth = (canvas.Width - BORDER_DISTANCE * 2) / GraphData.GridData.Count;
                CalculatedXStep = Math.Max(normalWidth, MinXStep);
                canvas.Width = CalculatedXStep * GraphData.GridData.Count + BORDER_DISTANCE * 2;

                // Calculate vertical Lines and text
                GraphData.ColumnPositions.Clear();
                for (int i = 0; i < GraphData.GridData.Count; ++i)
                {
                    GraphData.ColumnPositions.Add(new ColumnData(new Point(CalculatedXStep * i + CalculatedXStep / 2 + BORDER_DISTANCE, BORDER_DISTANCE - Y_COLUMN_OFFSET), new Point(CalculatedXStep * i + CalculatedXStep / 2 + BORDER_DISTANCE, canvas.Height - BORDER_DISTANCE - Y_COLUMN_OFFSET)));
                }

                // Calculate horizontal Lines
                for (int i = 0; i < GraphData.GridData.Count; ++i)
                {
                    if (GraphData.GridData[i].AllNumbers && GraphData.GridData[i].UniquEntries > StartApproximation)
                    {
                        GraphData.GridData[i].YPlacements.Clear();

                        for (int j = 0; j < NUMERIC_POINTS; ++j)
                        {
                            double labelNumber = (j == 0 ? GraphData.GridData[i].NumberRange.First : (j == NUMERIC_POINTS - 1 ? GraphData.GridData[i].NumberRange.Second : (GraphData.GridData[i].NumberRange.Second - GraphData.GridData[i].NumberRange.First) * (j / (double)NUMERIC_POINTS) + GraphData.GridData[i].NumberRange.First));

                            GraphData.GridData[i].YPlacements[labelNumber.ToString()] = (int)(j / (NUMERIC_POINTS + (GraphData.GridData[i].ContainsEmptyEntry ? 1 : 0)) * (canvas.Height - 2 * BORDER_DISTANCE) + (0.5 / (NUMERIC_POINTS + (GraphData.GridData[i].ContainsEmptyEntry ? 1 : 0)) * (canvas.Height - 2 * BORDER_DISTANCE)) + BORDER_DISTANCE - Y_COLUMN_OFFSET);
                        }

                        if (GraphData.GridData[i].ContainsEmptyEntry)
                        {
                            GraphData.GridData[i].YPlacements[EMPTY_FIELD] = (int)((NUMERIC_POINTS) / (NUMERIC_POINTS + (GraphData.GridData[i].ContainsEmptyEntry ? 1 : 0)) * (canvas.Height - 2 * BORDER_DISTANCE) + (0.5 / (NUMERIC_POINTS + (GraphData.GridData[i].ContainsEmptyEntry ? 1 : 0)) * (canvas.Height - 2 * BORDER_DISTANCE)) + BORDER_DISTANCE - Y_COLUMN_OFFSET);
                        }
                    }
                    else
                    {
                        var uniquValues = GraphData.GridData[i].Data.Distinct().Where(ee => ee[0] != '[').ToList();

                        sortList(ref uniquValues, GraphData.GridData[i].AllNumbers);

                        if (GraphData.GridData[i].ContainsEmptyEntry)
                        {
                            uniquValues.Add(EMPTY_FIELD);
                        }

                        for (int j = 0; j < uniquValues.Count; ++j)
                        {
                            GraphData.GridData[i].YPlacements[uniquValues[j]] = ((int)(j / (double)GraphData.GridData[i].UniquEntries * (canvas.Height - 2 * BORDER_DISTANCE) + (0.5 / (double)GraphData.GridData[i].UniquEntries * (canvas.Height - 2 * BORDER_DISTANCE)) + BORDER_DISTANCE - Y_COLUMN_OFFSET));
                        }
                    }
                }
                // END CHANGES
            }
            
            HideFiltered = (bool)FilterTxtBx.IsChecked;

            setFilters();
            drawScreen();
        }

        private void ShowGridSettings(object sender, RoutedEventArgs e)
        {
            settingsGrid.Visibility = Visibility.Visible;

            MinColumnWidthTxtBx.Text = MinXStep.ToString();
            //MaxUniqueEntriesTxtBx.Text = MaxUniqueEntries.ToString();
            BeginNumericAproxTxtBx.Text = StartApproximation.ToString();
            FilterTxtBx.IsChecked = HideFiltered;
        }

        private void PreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            int val;
            e.Handled = !Int32.TryParse(e.Text, out val);
        }

        private void ValidateCount(object sender, RoutedEventArgs e)
        {
            // Fill textboxes is empty
            if (BeginNumericAproxTxtBx.Text == "")
            {
                BeginNumericAproxTxtBx.Text = "10";
            }

            /*if (MaxUniqueEntriesTxtBx.Text == "")
            {
                MaxUniqueEntriesTxtBx.Text = "25";
            }*/

            if (MinColumnWidthTxtBx.Text == "")
            {
                MinColumnWidthTxtBx.Text = "300";
            }

            // Ensure NumericAproximation is not greater than total unique
            //BeginNumericAproxTxtBx.Text = (Int32.Parse(BeginNumericAproxTxtBx.Text) > Int32.Parse(MaxUniqueEntriesTxtBx.Text) ? MaxUniqueEntriesTxtBx.Text : BeginNumericAproxTxtBx.Text);
        }

        public void onScrollMove(object sender, RoutedEventArgs e)
        {
            UIElement canvasContainer = VisualTreeHelper.GetParent(canvas) as UIElement;
            Point relativeLocation = canvas.TranslatePoint(new Point(0, 0), canvasContainer);

            settingsGrid.Margin = new Thickness(-relativeLocation.X + 10, 10, 0, 0);
            settingsBtn.Margin = new Thickness(-relativeLocation.X + 10, 10, 0, 0);
        }
    }

    public class DisplayData
    {
        public DisplayData()
        {
            GridData = new List<DataEntry>();
            ColumnPositions = new List<ColumnData>();
        }

        public List<DataEntry> GridData { get; set; }
        public List<ColumnData> ColumnPositions { get; set; }
    }

    public class ColumnData
    {
        public ColumnData()
        {

        }

        public ColumnData(Point top, Point botumn)
        {
            Top = top;
            Botumn = botumn;
        }

        public Point Top { get; set; }
        public Point Botumn { get; set; }
    }
}
