   M S B A M L   `   `   `  ����  ParallelCordinates#    ParallelCordinates.MainWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     6F     � Title$  Parallel Coordinates��5   	   $	��356��6&   $	��531��63    � 
ResizeMode$ CanMinimize=�6?    � Icon$ icon.ico��5   	   .��5      � .+�5   
   �� ��5	      �� 5
       �� EndPoint$ 	0.504,1.5&�6&    �� 
StartPoint$ 
0.504,0.03&�6;   .��5      �  � Color$ 
GhostWhite��6#    � Offset$ 0Q�66   � 5      $ 
WhiteSmoke��6#   $ 3Q�66   5      5      �� 5   
   $
��Left=�6   $	��299��5      $��	10,10,0,0q�5      $	��Top=�5      $	��497��5      .@�5      �� $��Data Preparation��6   $	��130��60   .��5      � ���	#FFE5E5E5.+�5      �� -   5        $��Select Data Source��5      $
��Left=�6:   $��	12,30,0,0q�6U   $	��Top=�6h   $	��116��6�   6�   �� 5      -   5         ��Name$ FileNameLbl��5      $�� ��62   $
��Left=�6=   $��
131,28,0,0q�6X   $	��Top=�6l   $	��195��6�   �� 5      -   5        $��DataInterpretationBtn��5      $��View Data Interpretation��6:   $
��Left=�6]   $��
331,30,0,0q�6x   {�.  $	��Top=�6�   $	��141��6�   6�   �� 5      $��Visualization Method��6   $
��Left=�6;   $��9,73,0,0q�6V   $	��Top=�6h   $	��140��6�   $��14(�6�   	� 5      -   5        $ ��Parallel Coordinates in 2D��5   "   $
��Left=�6G   $��
43,107,0,0q�6b   $	��Top=�6v    d� 	IsChecked$
 TrueY�6�   $	��161��6�   $��19��6�   �� 5      -   5        $��	LaunchBtn��5      $��Launch Visualization��6.   $
��Left=�6M   $��
43,219,0,0q�6h   $	��Top=�6|   $	��399��6�   $��22��6�   {�.  6�   �� 5       $��Visualization Constraints��6   $
��Left=�6@   $��
239,73,0,0q�6[   $	��Top=�6o   $	��180��6�   $��14(�6�   �� 5!      -   5        $��MinColumnWidthTxtBx��5!      $
��Left=�69   $��23��6T   $��394,106,0,0q�6`   	 �� TextWrapping$
	 Wrap=�6u   $	��100��6�   $	��Top=�6�   $��30��6�   6�   �� 5"      $��Min Column Width: ��6   $
��Left=�69   $��268,102,0,0q�6T   $	��Top=�6i   �� 5#      $��px��6   $
��Left=�6)   $��420,102,0,0q�6D   $	��Top=�6Y   $��22��6q   �� 5$      -   5        $��MaxUniqueEntriesTxtBx��5$      $
��Left=�6;   $��23��6V   $��394,133,0,0q�6b   $
	 Wrap=�6w   $��25��6�   $	��Top=�6�   $��30��6�   6�   �� 5%      $��Max Unique Entries:��6   $
��Left=�6:   $��268,129,0,0q�6U   $	��Top=�6j   �� 5&      -   5        $��BeginNumericAproxTxtBx��5&      $
��Left=�6<   $��23��6W   $��394,160,0,0q�6c   $
	 Wrap=�6x   $��10��6�   $	��Top=�6�   $��30��6�   6�   �� 5'      $��Begin Numeric Aprox:��6   $
��Left=�6;   $��268,156,0,0q�6V   $	��Top=�6k   �� 5(      $��Hide Filtered Results��6   $
��Left=�6<   $��268,181,0,0q�6W   $	��Top=�6l   �� 5)      -	   5        $��FilterTxtBx��5)   *   $�� ��6   $
��Left=�6=   $��402,188,0,0q�6X   $	��Top=�6m   5*      5+      �� 5,      $
��Help��6   $	��130��6$   .��5-      � ���	#FFE5E5E5.+�5.      �� $
��Left=�6!   $	��261��5/      $��4,3,0,0q�50      $	��Top=�51      $	��479��52      .@�53      �� $��
File Input��6"   $	��130��66   .��54      � ���	#FFE5E5E5.+�55   "   �� $
��Left=�6,   $��7,2,0,0q�56      $
��Wrap=�57      $	��Top=�58      $	��462��59      $	��227��6+   �� 69   $!�Accepted Data Input Formats��6=   �� 6b   �� 6n   $�        .xlsx��6r   �� 6�   $� .txt��6�   �� 6�   �� 6�   �� 6�   �� 6�   $�Expected File Format��6�   �� 6�   �� 6�   $�        .xlsx��6�   �� 6  �� 6  $a�[                Beginning at cell A1, fill row 1 with attribute fields, one per cell. Every��6  �� 6x  �� 6�  $<�6                subsequent row is a single data entry.��6�  �� 6�  �� 6�  $�        .txt��6�  �� 6�  �� 6�  $i�c                Every line in the text file is one full data entry. Entry data fields are delimited��6�  �� 6k  �� 6w  $g�a                by a single tab character. If there is no value for a field, simply enter another��6{  �� 6�  �� 6�  $A�;                tab and begin entering the next data field.��6�  �� 6;  �� 6G  $�General��6K  �� 6\  �� 6h  $_�Y        Empty data entries will be replaced with [Not Available]. Additionally, if a data��6l  �� 6�  �� 6�  $`�Z        entries are surrounded by [] characters it will be treated as an empty data filed.��6�  6D  5:      5;      �� 5<      $��Input Arguments��6"   $	��130��6;   .��5=      � ���	#FFE5E5E5.+�5>   "   �� $
��Left=�6,   $��7,2,0,0q�5?      $
��Wrap=�5@      $	��Top=�5A      $	��462��5B      $	��227��6+   �� 69   $�Input Arguments��6=   �� 6V   �� 6b   $�        ��6f   �� 6x   �� 6�   $ �        Min Column Width: ��6�   �� 6�   �� 6�   $J�D                Define the minimum number of pixels between columns.��6�   �� 6
  �� 6  $�	��6  �� 6)  �� 65  $"�        Max Unique Entries: ��69  �� 6_  �� 6k  $Z�T                Columns with more than this number of unique non-numeric entries are��6o  �� 6�  �� 6�  $&�                 filtered out.   ��6�  �� 6  �� 6  $�	��6  �� 6&  �� 62  $#�        Begin Numeric Aprox: ��66  �� 6]  �� 6i  $^�X                If a column containing only numeric or empty values exceeds this number,��6m  �� 6�  �� 6�  $a�[                than points are not directly mapped to this column but rather approximated ��6�  �� 6D  �� 6P  $:�4                based on the range of its extremes. ��6T  �� 6�  �� 6�  $�	 ��6�  �� 6�  �� 6�  $�	��6�  6�  5C      5D      �� 5E      $��Features��6"   $	��130��64   .��5F      � ���	#FFE5E5E5.+�5G   "   �� $
��Left=�6,   $��7,2,0,0q�5H      $
��Wrap=�5I      $	��Top=�5J      $	��462��5K      $	��227��6+   �� 69   $�View Data Interpretation��6=   �� 6_   �� 6k   $b�\        This feature displays up to the first 21 entries of your data to verify the provided��6o   �� 6�   �� 6�   $/�)        input file was parsed correctly. ��6�   �� 6  �� 6$  �� 6*  �� 66  $ �Parallel Coordinates in 2D��6:  �� 6^  �� 6j  $Y�S        A method of viewing data in two dimensions. Note that for each column there��6n  �� 6�  �� 6�  $W�Q        is the ability to click on it and drag it to a new location, inserting it��6�  �� 66  �� 6B  $Y�S        between the columns the mouse up event occurs between. Additionally, points��6F  �� 6�  �� 6�  $]�W        can be filtered out by clicking and dragging the cursor on portions of a single��6�  �� 6  �� 6   $Y�S        column. Clicking again on the column in question will free the data filter.��6$  �� 6�  �� 6�  $�	 ��6�  �� 6�  �� 6�  $�	��6�  6�  5L      5M      5N      5O      5P      �� 5Q      $��About��6   $��130px��6%   .��5R      � ���	#FFE5E5E5.+�5S      �� $
��Left=�6    $��	10,10,0,0q�5T      $
��Wrap=�5U      $	��Top=�5V      $	��471��5W      $	��247��6   �� 6-   $8�2Parallel Coordinates: A data visualization method.��61   �� 6m   �� 6y   �� 6   �� 6�   $�Developed By��6�   �� 6�   $� ��6�   �� 6�   �� 6�   $�        Aaron Battershell��6�   �� 6�   �� 6�   �� 6�   �� 6  $�Written With��6	  �� 6  �� 6+  $3�-        Windows Presentation Foundation (WPF)��6/  �� 6f  �� 6r  �� 6x  �� 6�  $�View the source at��6�  �� 6�  �� 6�  $Q�K        GitHub.com/AaronBattershell/Projects/tree/master/ParallelCordinates��6�  �� 6	  �� 6  �� 6  �� 6'  �� 6-  �� 69  $!�(ɔ) 2015 Aaron Battershell��6=  �� 6a  �� 6m  �� 6s  �� 6  6�  5X      5Y      5Z      5[      5\      