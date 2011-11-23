#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
  
  /*GTK+ library initialization*/
  gtk_init(&argc,&argv);

  /*MainWindow is a pointer to a widget*/
  GtkWidget *MainWindow = NULL;

  /*Creating a label*/
  GtkWidget *label = gtk_label_new("This is Music Braille Compiler");

  /*This pointer is assigned a window*/
  MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(G_OBJECT(MainWindow),"delete-event",G_CALLBACK(gtk_main_quit),NULL);

  /*Set window title*/
  gtk_window_set_title(GTK_WINDOW(MainWindow),"Braille Music Compiler");

  /*Set window position*/
  gtk_window_set_position((GtkWindow *)MainWindow, GTK_WIN_POS_CENTER);

  /*Adding the label to the window*/
  gtk_container_add((GtkContainer *) MainWindow,label);

  /*Showing the window*/
  gtk_widget_show_all(MainWindow);
  gtk_main();
  
  return EXIT_SUCCESS;
}
