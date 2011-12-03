#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "new.h"
#include "open.h"
#include "save.h"


GtkWidget * createMenubar(GtkWidget *window)
{
	
	GtkWidget *menubar = gtk_menu_bar_new();
	GtkAccelGroup *accel_group = gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);
	
	//creation of the file menu
	GtkWidget *filemenu = gtk_menu_new();
  
	GtkWidget *	file = gtk_menu_item_new_with_mnemonic("_File");
	
	GtkWidget *new = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, NULL);
	g_signal_connect(G_OBJECT(new), "activate", 
	                 G_CALLBACK(new_file), accel_group);
	gtk_widget_add_accelerator(new, "activate", accel_group,GDK_n, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
		
	GtkWidget *open = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, accel_group);
	g_signal_connect(G_OBJECT(open), "activate", 
	                 G_CALLBACK(open_file), accel_group);
	gtk_widget_add_accelerator(open, "activate", accel_group,GDK_o, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	
	GtkWidget *sep1 = gtk_separator_menu_item_new();
	
	GtkWidget *save = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE, accel_group);
	g_signal_connect(G_OBJECT(save), "activate", 
	                 G_CALLBACK(save_file), accel_group);
	gtk_widget_add_accelerator(save, "activate", accel_group,GDK_s, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	
	GtkWidget *saveas = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE_AS, accel_group);
	g_signal_connect(G_OBJECT(saveas), "activate", 
	                 G_CALLBACK(save_file_as), accel_group);
	gtk_widget_add_accelerator(saveas, "activate", accel_group,GDK_s, GDK_CONTROL_MASK | GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
	
	
	GtkWidget *sep2= gtk_separator_menu_item_new();

	GtkWidget *quit = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, NULL);
	g_signal_connect(G_OBJECT(quit), "activate", 
	                 G_CALLBACK(gtk_main_quit), accel_group);
	gtk_widget_add_accelerator(quit, "activate", accel_group,GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE); 


	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), new);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), sep1);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), save);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), saveas);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), sep2);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);


	return menubar;
}
