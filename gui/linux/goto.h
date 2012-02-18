#ifndef GOTO_H
#define GOTO_H


void goto_next_prev(GtkWidget * widget, BrailleMusicEditor *editor, char n_p); 

void goto_next(GtkWidget * widget, BrailleMusicEditor *editor);

void goto_prev(GtkWidget * widget, BrailleMusicEditor *editor); 

void goto_num(GtkWidget * widget, BrailleMusicEditor *editor); 

void goto_num_(unsigned int n, GtkTextBuffer *buffer);

#endif
