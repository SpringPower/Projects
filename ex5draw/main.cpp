#include <iostream>
#include <assert.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <algorithm>

using namespace std;

void Bla(ALLEGRO_COLOR color, ALLEGRO_DISPLAY *ptDisplay)
{
    char *output = "home/aviv/csparout.png";
    std::vector<double> atValues;
    atValues.reserve(100000);
    double dMax = 0;
    ALLEGRO_BITMAP *ptBitmap = al_create_bitmap(1024, 768);

    for (int i=0; i<100000; ++i)
    {
        double dVal;
        cin>>dVal;

        if (i % 1000)
        {
            cout<<i;
        }

        atValues.push_back(dVal);
        if (dVal > dMax)
        {
            dMax = dVal;
        }
    }

    std::sort(atValues.begin(), atValues.end());

    cout<<"sorted"<<endl;

    al_set_target_bitmap(ptBitmap);
    al_clear_to_color(al_map_rgb(255,255,255));

    for (int i=0; i<100000-1; ++i)
    {
        al_draw_line((atValues[i]/dMax)*1024, 768-i*700.0/100000, (atValues[i+1]/dMax)*1024, 768-(i+1)*700.0/100000, color, 1.0);
    }

    al_flip_display();

    al_set_target_backbuffer(ptDisplay);

    al_draw_bitmap(ptBitmap, 0, 0, 0);

    al_flip_display();

    assert(al_save_bitmap("/home/aviv/expout.png", ptBitmap));

    cout<<"saved to "<<output<<endl;
}

int main()
{
    cout << "Hello World!" << endl;
    double dBla;

    al_init();

    assert(al_init_image_addon());
    assert(al_init_primitives_addon());

    ALLEGRO_DISPLAY *ptDisplay = al_create_display(1024, 768);

    Bla(al_map_rgb(255,0,0), ptDisplay);

    sleep(5000);

    return 0;
}

