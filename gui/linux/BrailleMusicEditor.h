#ifndef BRAILLEMUSICEDITOR_H
#define BRAILLEMUSICEDITOR_H

/**
 * \file BrailleMusicEditor.h
 * \author Team BMC editor 
 */

//store the widgets which are in the Braille Music Editor
/**
 *\struct BrailleMusicEditor
 *\brief This structure holds pointers to the objects that build the window, its menus ...

 * The structure BrailleMusicEditor was necessary for purposes of not using global variables which can be harmfull to the program.
 * Thus, the structure holds everything necessary to the program.


 */


typedef struct
{
    GtkWidget *window; /*!< A pointer to the window.*/
    GtkWidget *vbox; /*!< A pointer to the container that organizes all its widgets vertically.*/
    GtkWidget *hbox; /*!< A pointer to the container that organizes all its widgets horizontally/*/
    GtkWidget *menubar;/*!< A pointer to the menubar.*/
    GtkWidget *toolbar;/*! A pointer to the toolbar (with all the shortcuts).*/
    GtkWidget *edit_scrollbar;/*!< A pointer to the editing scrollbar.*/
    GtkWidget *score_scrollbar;/*!< A pointer to the partiture scrollbar.*/
    GtkWidget *error_scrollbar;/*!< A pointer to the error messages textview scrollbar.*/
    GtkWidget *textview;/*!< A pointer to the text view (the editing part of the window).*/
    GtkWidget *score_view;/*!< A pointer to the partiture view (the right part of the window).*/ 
    GtkWidget *error_view;/*!< A pointer to the error messages textview.*/ 
    gchar     *filename;/*!< A pointer to the name of the opened file.*/ 
} BrailleMusicEditor;

#endif
