#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

class Song {
    friend ostream &operator<<(ostream &os, const Song &s);
    string name;
    string artist;
    int rating;
public:
    Song() = default;
    Song(string name, string artist, int rating)
            : name{name}, artist{artist}, rating{rating} {}
    string get_name() const {
        return name;
    }
    string get_artist() const {
        return artist;
    }
    int get_rating() const {
        return rating;
    }
    
    bool operator<(const Song &rhs) const  {
        return this->name < rhs.name;
    }
    
    bool operator==(const Song &rhs) const  {
        return this->name == rhs.name;
    }
};

ostream &operator<<(ostream &os, const Song &s) {
    os << setw(20) << left << s.name
       << setw(30) << left << s.artist
       << setw(6) << right << s.rating;
       return os;
}

void display_menu() {
    cout << "\nF - Play First Song" << endl;
    cout << "N - Play Next song" << endl;
    cout << "P - Play Previous song" << endl;
    cout << "A - Add and play a new Song at current location" << endl;
    cout << "L - List the current playlist" << endl;
    cout << "===============================================" << endl;
    cout << "Enter a selection (Q to quit): ";
}

void play_current_song(const Song &song) {
    // This function displays 
    // Playing: followed by the song that is playing
   
    cout << "Playing:" << endl;
    cout << song << endl;
}

void display_playlist(const list<Song> &playlist, const Song &current_song) {
    // This function displays the current playlist 
    // and then the current song playing.
    
    
    cout << setw(20) << left << "\nTitle"
         << setw(30) << left << "Artist"
         << setw(6) << right << "Rating" << endl << endl;
    
    auto it = playlist.begin();
    while (it!= playlist.end()) {
        cout << *it << endl;
        it++;
    }
    
    cout << endl;
    cout << "Current song:" << endl;
    cout << current_song << endl;
}

int main() {

    list<Song> playlist{
            {"God's Plan",        "Drake",                     5},
            {"Never Be The Same", "Camila Cabello",            5},
            {"Pray For Me",       "The Weeknd and K. Lamar",   4},
            {"The Middle",        "Zedd, Maren Morris & Grey", 5},
            {"Wait",              "Maroon 5",                  4},
            {"Whatever It Takes", "Imagine Dragons",           3}          
    };
    
    list<Song>::iterator current_song = playlist.begin();
    list<Song>::iterator end_check = playlist.end();
    end_check--;
    
    char test{};
    
    do {
        display_menu();
        cin >> test;
        
        if (!isalpha(test)) {
            cout << "Please enter valid character" << endl;
            continue;
        }

        char test2 = toupper(test);
        switch(test2) {
            case 'F':
                    current_song = playlist.begin();
                    play_current_song(*current_song);
                    break;
            
            case 'N': 
                
                    if (current_song == end_check) {
                        current_song = playlist.begin();
                        play_current_song (*current_song);
                        
                    }
                    else {
                        
                        current_song++;
                        play_current_song(*current_song);
                        
                    }
                    break;
                    
            
            case 'P':
                    if (current_song == playlist.begin()) {
                        current_song = playlist.end();
                        current_song--;
                        play_current_song (*current_song);
                        break;
                    }
                    else {
                        current_song--;
                        play_current_song(*current_song);
                        break;
                    }
                    
            case 'A':
                    {auto it1 = current_song;
                    
                    cout << "Adding and playing new song" << endl;
                    
                    string namee{};
                    string a_name{};
                    int rating1;
                    
                    cin.ignore();
                    cout << "Enter song name: ";
                    getline (cin,namee);
                    
                    cout << "Enter song artist: ";
                    getline (cin,a_name);
                    
                    cout << "Enter rating: " ;
                    cin >> rating1;
                    
                    Song to_add {namee,a_name,rating1};
                    playlist.insert(it1,to_add);
                    
                    current_song--;
                    
                    play_current_song(*current_song);
                    break;}
                    
            case 'L':
                    display_playlist(playlist,*current_song);
                    break;
            
            case 'Q':
                    break;
                    
            default: 
                    cout << "Please enter valid character..." << endl;
                    break;
        }
        
    } while (test!='Q' && test!='q');

    cout << "Thanks for listening!" << endl;
    return 0;
}
