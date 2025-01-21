#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <iostream>
#include <gtkmm/cssprovider.h>
#include <gdkmm/screen.h>

class HelloWorld : public Gtk::Window
{
public:
    HelloWorld();
    virtual ~HelloWorld();

protected:
    void on_button_clicked();
    Gtk::Button m_button;
};

HelloWorld::HelloWorld() : m_button("Click Me!")
{
    // Set window properties
    set_title("NOTION");
    set_default_size(300, 150);

    // Customize button margins and size
    m_button.set_margin_top(20);        // Add top margin
    m_button.set_margin_bottom(20);     // Add bottom margin
    m_button.set_margin_start(20);      // Add left margin
    m_button.set_margin_end(20);        // Add right margin
    m_button.set_size_request(150, 50); // Set specific size for the button

    // Load and apply CSS styles with glowing effect
    auto css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data(R"(
        button {
            background-color: lightblue;
            color: darkblue;
            font: bold 14px Arial;
            border-radius: 10px;
            padding: 10px;
            transition: box-shadow 0.3s ease;
        }

        button:hover {
            box-shadow: 0 0 15px 5px rgba(0, 0, 255, 0.7);  /* Glowing blue on hover */
        }

        button:active {
            box-shadow: 0 0 25px 10px rgba(0, 0, 255, 1);   /* Stronger glow on click */
        }
    )");

    // Apply the CSS to the button's style context
    auto screen = Gdk::Screen::get_default();
    auto style_context = m_button.get_style_context();
    style_context->add_provider_for_screen(screen, css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Align the button in the center of the window
    m_button.set_halign(Gtk::ALIGN_CENTER);
    m_button.set_valign(Gtk::ALIGN_CENTER);

    // Connect signal
    m_button.signal_clicked().connect(sigc::mem_fun(*this, &HelloWorld::on_button_clicked));

    // Add the button to the window
    add(m_button);

    // Display all children
    show_all_children();
}

HelloWorld::~HelloWorld() {}

void HelloWorld::on_button_clicked()
{
    std::cout << "Button clicked!" << std::endl;
}

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "Hizbu.com");
    HelloWorld helloworld;
    return app->run(helloworld);
}
