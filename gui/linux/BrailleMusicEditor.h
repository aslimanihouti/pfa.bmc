#ifndef BRAILLEMUSICEDITOR_H
#define BRAILLEMUSICEDITOR_H


//store the widgets which are in the Braille Music Editor

typedef struct
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *menubar;
	GtkWidget *toolbar;
	GtkWidget *scrollbar;
	GtkWidget *scrollbar2;
	GtkWidget *textview;
	GtkWidget *rightview;

	gchar     *filename;
} BrailleMusicEditor;

#endif
