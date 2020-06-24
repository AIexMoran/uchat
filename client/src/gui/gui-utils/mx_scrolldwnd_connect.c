#include "client.h"

static void mx_scroll_to_end(GtkAdjustment *adj) {
    static gdouble i = 0;
    gdouble x = gtk_adjustment_get_upper(adj);
    gdouble curr = gtk_adjustment_get_value(adj) + gtk_adjustment_get_page_size(adj);

    if (curr <= x && curr >= x - (x - i))
        if (i < x)
            gtk_adjustment_set_value(adj, x);
    i = x;
}

/*
 * Do GtkScrolledWindow autoscroll to down by name or pointer
 */
void mx_scrlldwnd_connect(gchar *name,
                          GtkWidget *scroll, GtkBuilder *builder) {
    GtkWidget *scrlldwnd = NULL;
    GtkAdjustment *adj = NULL;

    if (name)
        scrlldwnd = GTK_WIDGET(gtk_builder_get_object(builder, name));
    else
        scrlldwnd = scroll;
    adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrlldwnd));
    g_signal_connect(adj, "changed", G_CALLBACK(mx_scroll_to_end), NULL);
}
