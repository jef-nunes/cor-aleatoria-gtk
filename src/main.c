#include <gtk/gtk.h>
#include "lib/random.h"
#include "lib/constants.h"

GtkWidget *window;
GtkWidget *container_a;
GtkWidget *button;
GtkWidget *label_codigo_cor;

static void gerar_cor(GtkWidget *widget, gpointer data)
{
    // Gerar um valor aleatório de cor RGB
    int r = randint(0, RGB_MAX);
    int g = randint(0, RGB_MAX);
    int b = randint(0, RGB_MAX);
    
    // Alterar o texto da label
    char fmt_texto_rgb[1000];
    snprintf(fmt_texto_rgb, sizeof(fmt_texto_rgb), "RGB(%d, %d, %d)", r, g, b);
    gtk_label_set_text(GTK_LABEL(label_codigo_cor), fmt_texto_rgb);

    // Criando o CSS para alterar a cor da label
    char css[100];
    snprintf(css, sizeof(css), "label { color: rgb(%d, %d, %d); }", r, g, b);

    // Criando o provedor de CSS
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider, css);
    gtk_widget_set_name(GTK_WIDGET(label_codigo_cor), "colored-label");
    gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(label_codigo_cor)), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

static void activate(GtkApplication *app, gpointer user_data)
{
    // [Container A]
    container_a = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // [Label que mostra uma cor]
    label_codigo_cor = gtk_label_new("#000000");
    // Adicionado à hierarquia do container
    gtk_box_append(GTK_BOX(container_a), label_codigo_cor);

    // [Janela GTK]
    window = gtk_application_window_new(app);
    // Título
    gtk_window_set_title(GTK_WINDOW(window), "Hello");
    // Dimensões
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

    // [Botão hello world]
    button = gtk_button_new_with_label("Nova cor");
    // Dimensões
    gtk_widget_set_size_request(button, 100, 50);
    // Evento de click (signal connect)
    g_signal_connect(button, "clicked", G_CALLBACK(gerar_cor), NULL);
    // Adicionado ao container
    gtk_box_append(GTK_BOX(container_a), button);

    // Adicionando o container à hierarquia da janela
    gtk_window_set_child(GTK_WINDOW(window), container_a);

    // Renderizar janela
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
    // Ponteiro de aplicação GTK
    GtkApplication *app;
    // Status de retorno
    int status;
    // Nova aplicação GTK
    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    // Evento de ativação da janela (signal connect)
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    // Loop do aplicativo
    status = g_application_run(G_APPLICATION(app), argc, argv);
    // Liberar recursos
    g_object_unref(app);
    return status;
}
