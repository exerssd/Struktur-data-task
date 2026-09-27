#include <iostream>
#include <string>
using namespace std;

const int Max = 5;

struct Peserta {
    int NIM;
    string Nama;
    string Prodi;
    int Semester;
    float IPK;
};

Peserta peserta[Max];
int totalpeserta = 0;

struct Node {
    Peserta peserta;
    Node* next;
};
Node *head = nullptr, *tail = nullptr;

void addNode(Peserta p){
    Node* newnode = new Node();
    newnode->peserta = p;
    newnode->next = nullptr;

    if(head == nullptr){
        head = tail = newnode;
    } else {
        tail->next = newnode;
        tail = newnode;
    }
}

Peserta inputPeserta(){
    Peserta p;
    cout << "NIM      : "; cin >> p.NIM; cin.ignore();
    cout << "Nama     : "; getline(cin, p.Nama);
    cout << "Prodi    : "; getline(cin, p.Prodi);
    cout << "Semester : "; cin >> p.Semester;
    cout << "IPK      : "; cin >> p.IPK; cin.ignore();
    return p;
}

void addPeserta(){
    int add;
    cout << "Masukkan Jumlah yg ingin ditambah : ";
    cin >> add;
    cin.ignore();

    for(int i = 0; i < add; i++){
        cout << "Peserta ke - " << (i+1) <<endl;
        Peserta p = inputPeserta();

        if(totalpeserta < Max){
            peserta[totalpeserta] = p;
            totalpeserta++;
        } else {
            addNode(p);
            cout << "-> DAFTAR UTAMA PENUH. Masuk ANTRIAN" <<endl;
        }
    }
    cout << "Data berhasil ditambahkan."<<endl;
}

void tampilPeserta(){
    cout << "\n===== PESERTA UTAMA =====\n";
    if(totalpeserta == 0){
        cout << "(kosong)\n";
        return;
    }
    for(int i = 0; i < totalpeserta; i++){
        cout << "Peserta (" << (i+1) <<") "<< endl;
        cout << "NIM      : " << peserta[i].NIM      << endl;
        cout << "Nama     : " << peserta[i].Nama     << endl;
        cout << "Prodi    : " << peserta[i].Prodi    << endl;
        cout << "Semester : " << peserta[i].Semester << endl;
        cout << "IPK      : " << peserta[i].IPK      << endl;
    }
}

void tampilAntrian(){
    cout << "\n===== DAFTAR TUNGGU (ANTRIAN) =====\n";
    if(head == nullptr){
        cout << "(kosong)\n";
        return;
    }
    Node* current = head;
    int i = 1;
    while(current != nullptr){
        cout << "Antrian" << i++ <<endl;
        cout << "NIM      : " << current->peserta.NIM      << endl;
        cout << "Nama     : " << current->peserta.Nama     << endl;
        cout << "Prodi    : " << current->peserta.Prodi    << endl;
        cout << "Semester : " << current->peserta.Semester << endl;
        cout << "IPK      : " << current->peserta.IPK      << endl;
        current = current->next;
    }
}

void CariPeserta(){
    int target;
    cout<<"Masukkan NIM yang dicari : ";cin>>target;
    for(int i = 0; i<totalpeserta;i++){
        if(target == peserta[i].NIM){
            cout<<"Peserta dengan NIM "<< target <<" Ditemukan!"<<endl;
            return;
        }
    }
    cout<<"Peserta dengan NIM "<<target<<" tidak ditemukan."<<endl;
}

void hapusArray(){
    int target;
    cout<<"Masukkan NIM peserta yang ingin di batalkan :";cin>>target;
    for(int i = 0; i<totalpeserta;i++){
        if(target == peserta[i].NIM){
            for(int j = i;j<totalpeserta-1;j++){
                peserta[j] = peserta[j + 1];
            }
            totalpeserta--;
            cout<<"Sukses dibatalkan!"<<endl;
            return;
        }
    }
    cout<<"Peserta dengan NIM "<<target<<" Tidak Ditemukan"<<endl;
}


void TambahDariDaftarAntrian(){
    if(head == nullptr){
        cout<<"Antrian Kosong"<<endl;
        return;
    }

    if (totalpeserta < Max){
        peserta[totalpeserta] = head->peserta;
        totalpeserta++;

        Node* temp = head;
        head = head->next;

        if(head == nullptr){
            tail = nullptr;
        }
        delete temp;
        cout<<"Menambah Peserta Dari Daftar Antrian."<<endl;
        return;
    }
    cout<<"Mohon Maaf Peserta Sedang Penuh."<<endl;
}

void HapusDariAntrian(){
    int target;
    cout<<"Masukkan NIM yang ingin dihapus dari daftar antrian :";cin>>target;
    if(head == nullptr){
        cout<<"Daftar Antrian Kosong"<<endl;
        return;
    }
    if(head->peserta.NIM == target){
        Node* hapus = head;
        head = head->next;
        if(head == nullptr){
        tail = nullptr;
        }
        delete hapus;
        cout<<"Sukses Dihapus"<<endl;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr && temp->next->peserta.NIM != target){
        temp = temp->next;
    }
    if(temp->next != nullptr){
        Node* hapus = temp->next;
        temp->next = hapus->next;
        if(hapus == tail){
            tail = temp;
        }
        cout<<"Sukses Dihapus"<<endl;
        delete hapus;
    }
}
void menu(){
    int pilih;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Tambah Peserta\n";
        cout << "2. Lihat Peserta Utama\n";
        cout << "3. Lihat Daftar Tunggu\n";
        cout << "4. Cari Peserta (NIM)\n";
        cout << "5. Batalkan Peserta Utama\n";
        cout << "6. Tambah Peserta dari Antrian\n";
        cout << "7. Hapus Peserta dari Antrian\n";
        cout << "0. Keluar\n";
        cout << "Pilih Menu(0-7) : ";
        cin >> pilih;
        cin.ignore();

        switch (pilih){
            case 1: addPeserta(); break;
            case 2: tampilPeserta(); break;
            case 3: tampilAntrian(); break;
            case 4: CariPeserta();break;
            case 5: hapusArray();break;
            case 6: TambahDariDaftarAntrian();break;
            case 7: HapusDariAntrian();break;
            case 0: cout << "Keluar...\n"; break;
            default: cout << "Menu tidak valid.\n";
        }
    } while(pilih != 0);
}

int main(){
    menu();
    return 0;
}