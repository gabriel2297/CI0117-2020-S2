#include <gtk/gtk.h>
#include <stdlib.h>
//#include "../Model/mapper.h"


static void inicial_message(GtkWidget * widget, gpointer data) {
  g_print("Pokemon Go Battle Simulator\n");
}


static void my_callback(GObject *source_object, GAsyncResult *res, gpointer user_data) {}

/* static void start_async(GTask *task, gpointer source_object, gpointer task_data, GCancellable *cancellable) {
    start_race();
}
  */
static void start_clicked(){
    GCancellable *cancellable = g_cancellable_new();
    GTask *task = g_task_new(g_object_new(G_TYPE_OBJECT, NULL), cancellable, my_callback, NULL);
    g_task_run_in_thread(task, start_async);
    g_object_unref(task);
}

static void activate(GtkApplication* app, gpointer user_data){
    GtkWidget * window;
    GtkWidget * button;
    GtkWidget * button_box;

  window = gtk_application_window_new(app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 300,500);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button = gtk_button_new_with_label("Pokemon Go Simulator");
  g_signal_connect(button, "clicked", G_CALLBACK (inicial_message), NULL);
  g_signal_connect_swapped(button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (button_box), button);

  gtk_widget_show_all(window);
}


int main(int argc, char * argv[]){
    GtkApplication * app;
    int status;

    app = gtk_application_new("PthreadMon - Pokemon Go Simulator", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}