#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <utility>
#include <cctype>

using namespace std;

struct Movie {
    string title;
    string genre;
    double rating;
};

string toLowerCase(string s) {
    for (char &c : s)
        c = tolower(c);
    return s;
}

double similarityScore(const Movie &m, string prefGenre, double prefRating) {
    double score = 0;
    if (m.genre == prefGenre)
        score += 5;
    score += (10 - abs(m.rating - prefRating));
    return score;
}

void merge(vector<pair<double,int>> &a, int l, int m, int r) {
    vector<pair<double,int>> temp;
    int i = l, j = m + 1;

    while (i <= m && j <= r) {
        if (a[i].first > a[j].first)
            temp.push_back(a[i++]);
        else
            temp.push_back(a[j++]);
    }

    while (i <= m) temp.push_back(a[i++]);
    while (j <= r) temp.push_back(a[j++]);

    for (int k = 0; k < (int)temp.size(); k++)
        a[l + k] = temp[k];
}

void mergeSort(vector<pair<double,int>> &a, int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    merge(a, l, m, r);
}

int main() {
    ios::sync_with_stdio(false);

    vector<Movie> movies = {
        {"Inception","Sci-Fi",8.8},
        {"Interstellar","Sci-Fi",8.6},
        {"Gravity","Sci-Fi",7.7},
        {"Avatar","Sci-Fi",7.8},
        {"The Martian","Sci-Fi",8.0},
        {"Blade Runner 2049","Sci-Fi",8.1},
        {"Arrival","Sci-Fi",7.9},

        {"The Dark Knight","Action",9.0},
        {"Avengers","Action",8.0},
        {"KGF","Action",8.2},
        {"Bahubali","Action",8.1},
        {"John Wick","Action",7.9},
        {"Mad Max Fury Road","Action",8.1},
        {"Gladiator","Action",8.5},

        {"Joker","Drama",8.5},
        {"Forrest Gump","Drama",8.8},
        {"The Shawshank Redemption","Drama",9.3},
        {"Fight Club","Drama",8.8},
        {"Parasite","Drama",8.5},

        {"Titanic","Romance",7.9},
        {"La La Land","Romance",8.0},
        {"The Notebook","Romance",7.8},
        {"Before Sunrise","Romance",8.1},

        {"3 Idiots","Comedy",8.4},
        {"The Hangover","Comedy",7.7},
        {"Superbad","Comedy",7.6},

        {"Dangal","Sports",8.4},
        {"Chak De India","Sports",8.2},
        {"Moneyball","Sports",7.6},

        {"Se7en","Thriller",8.6},
        {"Gone Girl","Thriller",8.1},
        {"Shutter Island","Thriller",8.2}
    };

    int choice;

    do {
        cout << "\n===== MOVIE RECOMMENDATION SYSTEM =====\n";
        cout << "1. View all movies\n";
        cout << "2. Get movie recommendations\n";
        cout << "3. Rate a movie\n";
        cout << "4. Add a new movie\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            cout << "\n===== ALL AVAILABLE MOVIES =====\n";
            for (auto &m : movies)
                cout << m.title << " (" << m.genre
                     << ", Rating: " << m.rating << ")\n";
            break;
        }

        case 2: {
            string prefGenre;
            double prefRating;

            cout << "\nEnter preferred genre: ";
            cin >> prefGenre;
            cout << "Enter minimum rating: ";
            cin >> prefRating;

            vector<pair<double,int>> scored;

            for (int i = 0; i < (int)movies.size(); i++) {
                if (movies[i].genre == prefGenre &&
                    movies[i].rating >= prefRating) {
                    double score =
                        similarityScore(movies[i], prefGenre, prefRating);
                    scored.push_back({score, i});
                }
            }

            if (scored.empty()) {
                cout << "\nNo movies match your criteria.\n";
                break;
            }

            mergeSort(scored, 0, scored.size() - 1);

            cout << "\n===== RECOMMENDED MOVIES =====\n";
            for (auto &p : scored) {
                Movie &m = movies[p.second];
                cout << m.title << " (" << m.genre
                     << ", Rating: " << m.rating << ")\n";
            }
            break;
        }

        case 3: {
            string movieName;
            double newRating;

            cout << "\nEnter movie name to rate: ";
            cin.ignore();
            getline(cin, movieName);

            string movieLower = toLowerCase(movieName);
            bool found = false;

            cout << "Enter your rating (0 - 10): ";
            cin >> newRating;

            for (auto &m : movies) {
                if (toLowerCase(m.title) == movieLower) {
                    m.rating = (m.rating + newRating) / 2.0;
                    cout << "Rating updated successfully.\n";
                    cout << "New average rating: " << m.rating << endl;
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "Movie not found.\n";

            break;
        }

        case 4: {
            string title, genre;
            double rating;

            cout << "\nEnter movie name: ";
            cin.ignore();
            getline(cin, title);

            string newTitleLower = toLowerCase(title);
            bool exists = false;

            for (auto &m : movies) {
                if (toLowerCase(m.title) == newTitleLower) {
                    exists = true;
                    break;
                }
            }

            if (exists) {
                cout << "Movie already exists in the list.\n";
                break;
            }

            cout << "Enter genre: ";
            cin >> genre;
            cout << "Enter rating (0 - 10): ";
            cin >> rating;

            movies.push_back({title, genre, rating});
            cout << "Movie added successfully.\n";
            break;
        }

        case 5:
            cout << "\nExiting program. Thank you!\n";
            break;

        default:
            cout << "\nInvalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
