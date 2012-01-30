#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "BrailleMusicEditor.h"
#include "new.h"
#include "open.h"
#include "save.h"
#include "edit.h"
#include "window.h"

/**
 * \file menubar.c
 * \author Team BMC editor 
 */


/**
 * \fn void create_menubar(BrailleMusicEditor *editor)
 * \brief This function creates the menubar of the window (the menu containing open, edit...).
 * \param editor The structure in which to create the menubar.
 */


void create_menubar(BrailleMusicEditor *editor)
{
    editor->menubar = gtk_menu_bar_new();
    GtkAccelGroup *accel_group = gtk_accel_group_new();
    gtk_window_add_accel_group(GTK_WINDOW(editor->window), accel_group);
	
    //creation of the file submenu
    GtkWidget *filemenu = gtk_menu_new();
    
    //creation of the file submenu's items
    GtkWidget *file = gtk_menu_item_new_with_mnemonic("_File");
    GtkWidget *new = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, accel_group);
    g_signal_connect(G_OBJECT(new), "activate", G_CALLBACK(new_file), editor);
    gtk_widget_add_accelerator(new, "activate", accel_group,GDK_n, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    GtkWidget *open = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, accel_group);
    g_signal_connect(G_OBJECT(open), "activate", G_CALLBACK(open_file), editor);
    gtk_widget_add_accelerator(open, "activate", accel_group,GDK_o, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    GtkWidget *sep1 = gtk_separator_menu_item_new();
    GtkWidget *save = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE, accel_group);
    g_signal_connect(G_OBJECT(save), "activate", G_CALLBACK(save_file), editor);
    gtk_widget_add_accelerator(save, "activate", accel_group,GDK_s, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);	
    GtkWidget *saveas = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE_AS, accel_group);
    g_signal_connect(G_OBJECT(saveas), "activate", G_CALLBACK(save_file_as), editor);
    gtk_widget_add_accelerator(saveas, "activate", accel_group,GDK_s, GDK_CONTROL_MASK | GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
    GtkWidget *sep2= gtk_separator_menu_item_new();
    GtkWidget *quit = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, NULL);
    g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(window_destroy), editor);
    gtk_widget_add_accelerator(quit, "activate", accel_group,GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE); 

    //addition of the file submenu's items in the menu 
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), new);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), sep1);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), save);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), saveas);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), sep2);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
    gtk_menu_shell_append(GTK_MENU_SHELL(editor->menubar), file);


    //creation of the edit submenu	
    GtkWidget *editmenu = gtk_menu_new();
    
    //creation of the edit submenu's items
    GtkWidget *edit = gtk_menu_item_new_with_mnemonic("_Edit");
	
    //	GtkWidget *undo = gtk_image_menu_item_new_from_stock(GTK_STOCK_UNDO, accel_group);
    //	g_signal_connect(G_OBJECT(undo), "activate", 
    //               G_CALLBACK(), accel_group);
    //gtk_widget_add_accelerator(undo, "activate", accel_group,GDK_z, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    GtkWidget *cut = gtk_image_menu_item_new_from_stock(GTK_STOCK_CUT, accel_group);
    g_signal_connect(G_OBJECT(cut), "activate", G_CALLBACK(on_cut), editor);
    GtkWidget *copy = gtk_image_menu_item_new_from_stock(GTK_STOCK_COPY, accel_group);
    g_signal_connect(G_OBJECT(copy), "activate", G_CALLBACK(on_copy), editor);
    GtkWidget *paste = gtk_image_menu_item_new_from_stock(GTK_STOCK_PASTE, accel_group);
    g_signal_connect(G_OBJECT(paste), "activate", G_CALLBACK(on_paste), editor);
    GtkWidget *sep3= gtk_separator_menu_item_new();
    GtkWidget *select_all = gtk_image_menu_item_new_from_stock(GTK_STOCK_SELECT_ALL, accel_group);
    g_signal_connect(G_OBJECT(select_all), "activate", G_CALLBACK(on_select_all), editor);
    gtk_widget_add_accelerator(select_all, "activate", accel_group,GDK_a, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    
    /* GtkWidget *select = gtk_menu_item_new(); */
    /* g_signal_connect(G_OBJECT(select), "activate", */
    /*                  G_CALLBACK(on_select), editor); */
    /* gtk_widget_add_accelerator(select, "activate", accel_group,GDK_space, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE); */

    //addition of the edit submenu's items in the menu 
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit), editmenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(editmenu),cut);
    gtk_menu_shell_append(GTK_MENU_SHELL(editmenu),copy);
    gtk_menu_shell_append(GTK_MENU_SHELL(editmenu),paste);
    gtk_menu_shell_append(GTK_MENU_SHELL(editmenu),sep3);
    //	gtk_menu_shell_append(GTK_MENU_SHELL(editmenu),select);
    gtk_menu_shell_append(GTK_MENU_SHELL(editmenu),select_all);
    gtk_menu_shell_append(GTK_MENU_SHELL(editor->menubar), edit);

}
