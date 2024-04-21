#include <gtk/gtk.h>
#include <string.h>

typedef struct {
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *result_label;
    char operation; // Aggiungi un campo per memorizzare l'operazione selezionata
} CalculatorData;

void calculate(GtkWidget *widget, gpointer data) {
    CalculatorData *calc_data = (CalculatorData *)data;
    const char *op = gtk_button_get_label(GTK_BUTTON(widget));
    
    // Memorizza l'operazione selezionata
    calc_data->operation = op[0];
}

void calculate_result(GtkWidget *widget, gpointer data) {
    CalculatorData *calc_data = (CalculatorData *)data;
    
    // Ottieni i numeri dagli entry
    int num1 = atoi(gtk_entry_get_text(GTK_ENTRY(calc_data->entry1)));
    int num2 = atoi(gtk_entry_get_text(GTK_ENTRY(calc_data->entry2)));
    
    int result;
    char result_str[100];
    
    // Calcola il risultato in base all'operazione selezionata
    switch (calc_data->operation) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                gtk_label_set_text(GTK_LABEL(calc_data->result_label), "Errore: divisione per zero");
                return;
            }
            break;
        case '%':
            if (num2 != 0) {
                result = num1 % num2;
            } else {
                gtk_label_set_text(GTK_LABEL(calc_data->result_label), "Errore: divisione per zero");
                return;
            }
            break;
        default:
            gtk_label_set_text(GTK_LABEL(calc_data->result_label), "Operazione non valida");
            return;
    }
    
    // Aggiorna l'etichetta del risultato
    snprintf(result_str, sizeof(result_str), "Risultato: %d", result);
    gtk_label_set_text(GTK_LABEL(calc_data->result_label), result_str);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Crea la finestra principale
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calcolatrice");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // Crea un box verticale per organizzare i widget
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Crea i campi di testo per i numeri
    CalculatorData calc_data;
    calc_data.entry1 = gtk_entry_new();
    calc_data.entry2 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), calc_data.entry1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), calc_data.entry2, FALSE, FALSE, 0);

    // Crea i pulsanti per le operazioni
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    const char *operations[] = {"+", "-", "*", "/", "%"};
    for (int i = 0; i < 5; i++) {
        GtkWidget *button = gtk_button_new_with_label(operations[i]);
        gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 0);
        g_signal_connect(button, "clicked", G_CALLBACK(calculate), &calc_data);
    }

    // Crea il pulsante per l'uguale
    GtkWidget *equal_button = gtk_button_new_with_label("=");
    gtk_box_pack_start(GTK_BOX(hbox), equal_button, TRUE, TRUE, 0);
    g_signal_connect(equal_button, "clicked", G_CALLBACK(calculate_result), &calc_data);

    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    // Crea l'etichetta per il risultato
    calc_data.result_label = gtk_label_new("Risultato: ");
    gtk_box_pack_start(GTK_BOX(vbox), calc_data.result_label, FALSE, FALSE, 0);

    // Imposta il segnale per chiudere l'applicazione
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostra tutti i widget
    gtk_widget_show_all(window);

    // Esegui il loop dell'applicazione
    gtk_main();

    return 0;
}
