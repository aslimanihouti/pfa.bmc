#ifndef GOTO_H
#define GOTO_H

void load_braille_char(); 

void goto_next_prev(GtkWidget * widget, BrailleMusicEditor *editor, char n_p); 

void goto_next(GtkWidget * widget, BrailleMusicEditor *editor);

void goto_prev(GtkWidget * widget, BrailleMusicEditor *editor); 

#endif
