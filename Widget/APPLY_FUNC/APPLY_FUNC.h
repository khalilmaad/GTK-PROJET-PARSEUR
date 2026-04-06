#ifndef APPLY_FUNC_H_INCLUDED
#define APPLY_FUNC_H_INCLUDED

#include <gtk/gtk.h>

typedef struct wd Widget;

void apply_css(GtkWidget* mon_widget,const char* ma_class,const char* valeur);

void apply_attribut_fenetre(Widget*);

void apply_attribut_box(Widget*);

void apply_attribut_button(Widget*);

void apply_attribut_checkbutton(Widget*);

void apply_attribut_entry(Widget*);

void apply_attribut_frame(Widget*);

void apply_attribut_headerbar(Widget*);

void apply_attribut_image(Widget*);

void apply_attribut_label(Widget*);

void apply_attribut_scrollbar(Widget*);

void apply_attribut_buttonradio(Widget*);

void apply_attribut_menuitem(Widget*);

void apply_attribut_grid(Widget*);

void apply_attribut_paned(Widget*);

void apply_attribut_notebook(Widget* obj);

void apply_attribut_stack(Widget* obj);

void apply_attribut_expander(Widget* obj);

void apply_attribut_layout(Widget* obj);

void apply_attribut_revealer(Widget* obj);

void apply_attribut_listbox(Widget* obj);

void apply_attribut_flowbox(Widget* obj);

void apply_attribut_buttonbox(Widget* obj);

void apply_attribut_toolitem(Widget* obj);

void apply_attribut_toolbar(Widget* obj);

void apply_attribut_infobar(Widget* obj);

void apply_attribut_searchbar(Widget* obj);

void apply_attribut_togglebutton(Widget* obj);

void apply_attribut_linkbutton(Widget* obj);

void apply_attribut_spinbutton(Widget* obj);

void apply_attribut_switch(Widget* obj);

void apply_attribut_scalebutton(Widget* obj);

void apply_attribut_menubutton(Widget* obj);

void apply_attribut_progressbar(Widget* obj);

void apply_attribut_levelbar(Widget* obj);

void apply_attribut_spinner(Widget* obj);

void apply_attribut_scale(Widget* obj);

void apply_attribut_colorbutton(Widget* obj);

void apply_attribut_fontbutton(Widget* obj);

void apply_attribut_filechoosebutton(Widget* obj);

void apply_attribut_checkmenuitem(Widget* obj);

void apply_attribut_radiomenuitem(Widget* obj);

void apply_attribut_comboboxtext(Widget* obj);

void apply_attribut_separator(Widget* obj);

void apply_attribut_filechooserdialog(Widget* obj);

void apply_attribut_simulation(Widget* obj);

void apply_attribut_poisson(Widget* obj);

#endif // APPLY_FUNC_H_INCLUDED
