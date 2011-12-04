#ifndef BRAILLEMUSICEDITOR_H
#define BRAILLEMUSICEDITOR_H


//store the widgets which are in the Braille Music Editor

typedef struct
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *menubar;
	GtkWidget *toolbar;
	GtkWidget *scrollbar;
	GtkWidget *textview;

	gchar     *filename;
} BrailleMusicEditor;

#endif
