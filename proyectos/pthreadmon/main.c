#include <gtk/gtk.h>
#include <stdio.h>
#include "Controller/GameController/GameController.h"
#include "Controller/PlayerController/PlayerController.h"
#include "Model/mapper.h"
#include <stdlib.h>
#include <string.h>
int id_matrix[2][3];
char pokemonName1[200]; 
char pokemonName2[200];
char path[200] = "View/sprites/";
char path2[200] = "View/sprites/";
char pokemon1_hp[200];
char pokemon2_hp[200];
char pokemon1_energy[200];
char pokemon2_energy[200];
char pokemon1_moveNameAndDamage[200];
char pokemon2_moveNameAndDamage[200];
char estadisticas[500];
GtkWidget * image;
GtkWidget * button_box2; 
GtkWidget * button_box; 
GtkBuilder * builder; 
GtkWidget * window;
GtkWidget * second_window;
GtkWidget * third_window;
GtkEntry * text_entry;
GtkWidget * lbl_one;
GtkWidget * lbl_two;
GtkWidget * lbl_three;
GtkWidget * lbl_four;
GtkWidget * lbl_five;
GtkWidget * button;
GtkWidget * button2;
GtkComboBoxText * list_chooser_one;
GtkComboBoxText * list_chooser_two;
GtkComboBoxText * list_chooser_three;
GtkComboBoxText * list_chooser_four;
GtkComboBoxText * list_chooser_five;
GtkComboBoxText * list_chooser_six;
pthread_mutex_t mutex;

static void my_callback(GObject *source_object, GAsyncResult *res, gpointer user_data){}

static void start_async(GTask *task, gpointer source_object, gpointer task_data, GCancellable *cancellable)
{
    startGame(id_matrix);
}

/* void on_retry_button_clicked(GtkWidget * button2, gpointer data){
    GCancellable *cancellable = g_cancellable_new();
    GTask *task = g_task_new(g_object_new(G_TYPE_OBJECT, NULL), cancellable, my_callback, NULL);
    g_task_run_in_thread(task, start_async);
    g_object_unref(task);
    gtk_widget_hide(third_window);
    gtk_widget_show(second_window);
} */

void setPokemonName(int playerId, char * name){
    pthread_mutex_lock(&mutex);
    if (playerId == 1){
        strcpy(pokemonName1, name);
    }
    else {
        strcpy(pokemonName2, name);

    }
    pthread_mutex_unlock(&mutex);
}

char * getPokemonName(){
    return pokemonName1;
}

char * getPokemon2Name(){
    return pokemonName2;
}

void setPokemonHP(int playerId, int hp)
{
    if (playerId == 1)
    { 
        int n = sprintf(pokemon1_hp, "%s \nVida: %d", getPokemonName(), hp);
        gtk_label_set_text(GTK_LABEL(lbl_two), pokemon1_hp);
    }
    else
    {
        int n = sprintf(pokemon2_hp, "%s \nVida: %d", getPokemon2Name(), hp);
        gtk_label_set_text(GTK_LABEL(lbl_three), pokemon2_hp);
    }
}

void setWinnerInformation(int playerId, char * name) {
    if (playerId == 1)
    {
        int n = sprintf(pokemon1_hp, "Felicidades %s, el jugador %d es el ganador!\n", name, playerId);
        sprintf(pokemon2_hp, "-");
        gtk_label_set_text(GTK_LABEL(lbl_three), pokemon2_hp);
        gtk_label_set_text(GTK_LABEL(lbl_two), pokemon1_hp);
        n = sprintf(pokemon1_energy, "-");
        gtk_label_set_text(GTK_LABEL(lbl_four), pokemon1_energy);
        n = sprintf(pokemon2_energy, "-");
        gtk_label_set_text(GTK_LABEL(lbl_five), pokemon2_energy);
    }
    else {
        int n = sprintf(pokemon2_hp, "Felicidades %s, el jugador %d es el ganador!\n", name, playerId);
        gtk_label_set_text(GTK_LABEL(lbl_three), pokemon2_hp);
        sprintf(pokemon1_hp, "-");
        gtk_label_set_text(GTK_LABEL(lbl_two), pokemon1_hp);
        n = sprintf(pokemon2_energy, "-");
        gtk_label_set_text(GTK_LABEL(lbl_five), pokemon2_energy);
        n = sprintf(pokemon1_energy, "-");
        gtk_label_set_text(GTK_LABEL(lbl_four), pokemon1_energy);
    }
}

void setPokemonEnergy(int playerId, int energy, int chargedMove_energy, int pokemonNumber) 
{
    int n;
    if (playerId == 1)
    {
        switch(pokemonNumber) {
            case 0:
                n = sprintf(pokemon1_energy, "Energia acumulada: %d / %d\nPokemons: [o, o, o]", energy, chargedMove_energy);
                gtk_label_set_text(GTK_LABEL(lbl_four), pokemon1_energy);
                break;
            case 1:
                n = sprintf(pokemon1_energy, "Energia acumulada: %d / %d\nPokemons: [x, o, o]", energy, chargedMove_energy);
                gtk_label_set_text(GTK_LABEL(lbl_four), pokemon1_energy);
                break;
            case 2: 
                n = sprintf(pokemon1_energy, "Energia acumulada: %d / %d\nPokemons: [x, x, o]", energy, chargedMove_energy);
                gtk_label_set_text(GTK_LABEL(lbl_four), pokemon1_energy);
                break;
            default: 
                n = sprintf(pokemon1_energy, "Energia acumulada: %d / %d\nPokemons: [x, x, x]", energy, chargedMove_energy);
                gtk_label_set_text(GTK_LABEL(lbl_four), pokemon1_energy);
                break;
        }
    }
    else
    {
        switch(pokemonNumber) {
            case 0:
                n = sprintf(pokemon2_energy, "Energia acumulada: %d / %d\nPokemons: [o, o, o]", energy, chargedMove_energy);
                gtk_label_set_text(GTK_LABEL(lbl_five), pokemon2_energy);
                break;
            case 1:
                n = sprintf(pokemon2_energy, "Energia acumulada: %d / %d\nPokemons: [x, o, o]", energy, chargedMove_energy);
                gtk_label_set_text(GTK_LABEL(lbl_five), pokemon2_energy);
                break;
            case 2: 
                n = sprintf(pokemon2_energy, "Energia acumulada: %d / %d\nPokemons: [x, x, o]", energy, chargedMove_energy);
                gtk_label_set_text(GTK_LABEL(lbl_five), pokemon2_energy);
                break;
            default: 
                n = sprintf(pokemon2_energy, "Energia acumulada: %d / %d\nPokemons: [x, x, x]", energy, chargedMove_energy);
                gtk_label_set_text(GTK_LABEL(lbl_five), pokemon2_energy);
                break;
        }
    }
}

void setFastAttackName(int playerId, char * moveName, int damage)
{
    if (playerId == 1)
    { 
        int n = sprintf(pokemon1_moveNameAndDamage, "%s, usa ataque rapido!\nAtaque: %s\nDaño: %d\n", getPokemonName(), moveName, damage);
        gtk_label_set_text(GTK_LABEL(lbl_one), pokemon1_moveNameAndDamage);
    }
    else
    {
        int n = sprintf(pokemon2_moveNameAndDamage, "%s, usa ataque rapido!\nAtaque: %s\nDaño: %d\n", getPokemon2Name(), moveName, damage);
        gtk_label_set_text(GTK_LABEL(lbl_one), pokemon2_moveNameAndDamage);
    }
}

void setChargedAttackName(int playerId, char * moveName, int damage)
{
    if (playerId == 1)
    { 
        int n = sprintf(pokemon1_moveNameAndDamage, "%s, usa ataque cargado!\nAtaque: %s\nDaño: %d\n", getPokemonName(), moveName, damage);
        gtk_label_set_text(GTK_LABEL(lbl_one), pokemon1_moveNameAndDamage);
    }
    else
    {
        int n = sprintf(pokemon1_moveNameAndDamage, "%s, usa ataque cargado!\nAtaque: %s\nDaño: %d\n", getPokemon2Name(), moveName, damage);
        gtk_label_set_text(GTK_LABEL(lbl_one), pokemon2_moveNameAndDamage);
    }
}

void setPokemonStatistics(unsigned long pokemon_statistics[3][3], pokemon_t* player1_pokemons[MAX_POKEMONS_PER_PLAYER], pokemon_t* player2_pokemons[MAX_POKEMONS_PER_PLAYER])
{
    int n = sprintf(estadisticas, "Estadisticas del juego:\n \
        Duracion total: %lu segundos\n \
        Pokemons jugador 1:\n \
        \t- Duracion de %s: %lu segundos\n \
        \t- Duracion de %s: %lu segundos\n \
        \t- Duracion de %s: %lu segundos\n \
        Pokemons jugador 2:\n \
        \t- Duracion de %s: %lu segundos\n \
        \t- Duracion de %s: %lu segundos\n \
        \t- Duracion de %s: %lu segundos\n",
        pokemon_statistics[2][0],
        player1_pokemons[0]->pokemon_info->speciesName, pokemon_statistics[0][0],
        player1_pokemons[1]->pokemon_info->speciesName, pokemon_statistics[0][1],
        player1_pokemons[2]->pokemon_info->speciesName, pokemon_statistics[0][2],
        player2_pokemons[0]->pokemon_info->speciesName, pokemon_statistics[1][0],
        player2_pokemons[1]->pokemon_info->speciesName, pokemon_statistics[1][1],
        player2_pokemons[2]->pokemon_info->speciesName, pokemon_statistics[1][2]
    );
    gtk_label_set_text(GTK_LABEL(lbl_one), estadisticas);
    gtk_widget_show(button2);
}

void on_box1_changed(GtkComboBox * comboBox, gpointer data){
    id_matrix[0][0] = (int)gtk_combo_box_get_active(comboBox);
}

void on_box2_changed(GtkComboBox * comboBox, gpointer data){
    id_matrix[0][1] = (int)gtk_combo_box_get_active(comboBox);
}

void on_box3_changed(GtkComboBox * comboBox, gpointer data){
    id_matrix[0][2] = (int)gtk_combo_box_get_active(comboBox);
}
void on_box4_changed(GtkComboBox * comboBox, gpointer data){
    id_matrix[1][0] = (int)gtk_combo_box_get_active(comboBox);
}
void on_box5_changed(GtkComboBox * comboBox, gpointer data){
    id_matrix[1][1] = (int)gtk_combo_box_get_active(comboBox);
}
void on_box6_changed(GtkComboBox * comboBox, gpointer data){
    id_matrix[1][2] = (int)gtk_combo_box_get_active(comboBox);
}

void on_ready_button_clicked(GtkWidget * ready_button, gpointer data){
    /* Validación de datos */
    for (int i = 0; i < 3; ++i){
        for (int j = i + 1; j < 3; ++j){
            if ((id_matrix[0][i] == id_matrix[0][j]) || id_matrix[1][i] == id_matrix[1][j]){
                printf("ERROR: No se puede seleccionar dos pokemon de la misma especie\n");
                return;
            }
        }
    }
    
    GCancellable *cancellable = g_cancellable_new();
    GTask *task = g_task_new(g_object_new(G_TYPE_OBJECT, NULL), cancellable, my_callback, NULL);
    g_task_run_in_thread(task, start_async);
    g_object_unref(task);
    gtk_widget_hide(second_window);

    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "View/Interface.glade", NULL);
    third_window = GTK_WIDGET (gtk_builder_get_object (builder, "Battle_window")); 
    if (NULL == third_window)
    {
        fprintf(stderr, "Unable to file object with id \"Battle_window\" \n");
    }
    gtk_window_set_default_size(GTK_WINDOW(third_window), 440, 400);
    gtk_window_set_resizable (GTK_WINDOW(third_window), FALSE);
    lbl_one = GTK_WIDGET(gtk_builder_get_object(builder, "attack_info"));
    lbl_two = GTK_WIDGET(gtk_builder_get_object(builder, "pokemon1"));
    lbl_three = GTK_WIDGET(gtk_builder_get_object(builder, "pokemon2"));
    lbl_four = GTK_WIDGET(gtk_builder_get_object(builder, "energy1"));
    lbl_five = GTK_WIDGET(gtk_builder_get_object(builder, "energy2"));
    button_box2 = GTK_WIDGET(gtk_builder_get_object(builder, "retry_box"));
    button2 = GTK_WIDGET(gtk_builder_get_object(builder, "retry_button"));

    gtk_widget_hide(button2);
    //g_signal_connect (button2, "clicked", G_CALLBACK (on_retry_button_clicked), NULL);
    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(third_window);

}

void on_start_button_clicked(GtkWidget * start_button, gpointer data){

    GCancellable *cancellable = g_cancellable_new();
    GTask *task = g_task_new(g_object_new(G_TYPE_OBJECT, NULL), cancellable, my_callback, NULL);
    //g_task_run_in_thread(task, start_async);
    g_object_unref(task);
    gtk_widget_hide(window);

    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

    builder = gtk_builder_new();

    gtk_builder_add_from_file (builder, "View/Interface.glade", NULL);
    second_window = GTK_WIDGET (gtk_builder_get_object (builder, "second_window")); 
    if (NULL == second_window)
    {
        fprintf(stderr, "Unable to file object with id \"second_window\" \n");
    }

    lbl_one = GTK_WIDGET(gtk_builder_get_object(builder, "lbl1"));
    list_chooser_one = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "box1"));
    list_chooser_two = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "box2"));
    list_chooser_three = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "box3"));
    list_chooser_four = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "box4"));
    list_chooser_five = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "box5"));
    list_chooser_six = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "box6"));

    for (size_t i = 0; i < NUM_POKEMON; ++i){
        gtk_combo_box_text_append(list_chooser_one, NULL, (gchar *) get_pokemon_species_name(i));
        gtk_combo_box_text_append(list_chooser_two, NULL, (gchar *) get_pokemon_species_name(i));
        gtk_combo_box_text_append(list_chooser_three, NULL, (gchar *) get_pokemon_species_name(i));
        gtk_combo_box_text_append(list_chooser_four, NULL, (gchar *) get_pokemon_species_name(i));
        gtk_combo_box_text_append(list_chooser_five, NULL, (gchar *) get_pokemon_species_name(i));
        gtk_combo_box_text_append(list_chooser_six, NULL, (gchar *) get_pokemon_species_name(i));
    }
    button_box = GTK_WIDGET(gtk_builder_get_object(builder, "button_box"));
    button =  GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    
    /* Agregar los textos a los widgets de seleccionar pokemon */
    g_signal_connect (button, "clicked", G_CALLBACK (on_ready_button_clicked), NULL);
    g_signal_connect (list_chooser_one, "changed", G_CALLBACK (on_box1_changed), NULL);
    g_signal_connect (list_chooser_two, "changed", G_CALLBACK (on_box2_changed), NULL);
    g_signal_connect (list_chooser_three, "changed", G_CALLBACK (on_box3_changed), NULL);
    g_signal_connect (list_chooser_four, "changed", G_CALLBACK (on_box4_changed), NULL);
    g_signal_connect (list_chooser_five, "changed", G_CALLBACK (on_box5_changed), NULL);
    g_signal_connect (list_chooser_six, "changed", G_CALLBACK (on_box6_changed), NULL);

    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(second_window);

}


void on_window_destroyed(){
    pthread_mutex_destroy(&mutex);
    gtk_main_quit();
}

static void activate(GtkApplication *app, gpointer user_data){

    initialize_data();

    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

    builder = gtk_builder_new();

    gtk_builder_add_from_file (builder, "View/Interface.glade", NULL);

    window = GTK_WIDGET (gtk_builder_get_object (builder, "window1")); 
    if (NULL == window)
    {
        /* Print out the error. You can use GLib's message logging  */
        fprintf(stderr, "Unable to file object with id \"window1\" \n");
        /* Your error handling code goes here */
    }
    image = GTK_WIDGET(gtk_builder_get_object(builder, "logo"));
    button_box = GTK_WIDGET(gtk_builder_get_object(builder, "button_box"));
    button = GTK_WIDGET(gtk_builder_get_object(builder, "start_button"));
    text_entry = GTK_ENTRY(gtk_builder_get_object(builder, "name_entry"));
    g_signal_connect (button, "clicked", G_CALLBACK (on_start_button_clicked), NULL);
    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(window);
    gtk_main();
}

int main(int argc, char * argv[]){
    GtkApplication *app;
    int status;
    pthread_mutex_init(&mutex, NULL);
    app = gtk_application_new("pthreadmon.simulator", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
