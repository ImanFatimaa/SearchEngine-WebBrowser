
#pragma once
#include"FileContentFile1.h"
#include"searchengine.cpp"
namespace gui {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    using namespace std;
    // using namespace experimental::filesystem;

     /// <summary>
     /// Summary for MyForm
     /// </summary>
    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            //
            //TODO: Add the constructor code here
            //
        }

    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Button^ searchButton;
    private: System::Windows::Forms::ListBox^ resultsListBox;
    private: System::ComponentModel::Container^ components;
    private: System::Windows::Forms::ComboBox^ comboBox1;
    private:   System::Windows::Forms::Label^ titleLabel;

    private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel;

    protected:

    private:
        /// <summary>
        /// Required designer variable.
        /// </summary>


#pragma region Windows Form Designer generated code


        void InitializeComponent(void)
        {
            this->searchButton = (gcnew System::Windows::Forms::Button());
            this->resultsListBox = (gcnew System::Windows::Forms::ListBox());
            this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
            this->titleLabel = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            //
            // searchButton
            //
            this->searchButton->BackColor = System::Drawing::Color::Beige;
            this->searchButton->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->searchButton->ForeColor = System::Drawing::Color::Black;
            this->searchButton->Location = System::Drawing::Point(613, 143);
            this->searchButton->Name = L"searchButton";
            this->searchButton->Size = System::Drawing::Size(119, 31);
            this->searchButton->TabIndex = 1;
            this->searchButton->Text = L"Search";
            this->searchButton->UseVisualStyleBackColor = false;
            this->searchButton->Click += gcnew System::EventHandler(this, &MyForm::searchButton_Click);
            //
            // resultsListBox
            //
            this->resultsListBox->BackColor = System::Drawing::Color::Beige;
            this->resultsListBox->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->resultsListBox->ForeColor = System::Drawing::Color::Black;
            this->resultsListBox->ItemHeight = 16;
            this->resultsListBox->Location = System::Drawing::Point(1, 237);
            this->resultsListBox->Name = L"resultsListBox";
            this->resultsListBox->Size = System::Drawing::Size(744, 276);
            this->resultsListBox->TabIndex = 2;
            this->resultsListBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::resultsListBox_SelectedIndexChanged);
            //
            // comboBox1
            //
            this->comboBox1->BackColor = System::Drawing::Color::Beige;
            this->comboBox1->Font = (gcnew System::Drawing::Font(L"Arial", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->comboBox1->ForeColor = System::Drawing::Color::Black;
            this->comboBox1->FormattingEnabled = true;
            this->comboBox1->Location = System::Drawing::Point(12, 143);
            this->comboBox1->Name = L"comboBox1";
            this->comboBox1->Size = System::Drawing::Size(557, 31);
            this->comboBox1->TabIndex = 3;
            //
            // titleLabel
            //
            this->titleLabel->AutoSize = true;
            this->titleLabel->Font = (gcnew System::Drawing::Font(L"Arial", 40, System::Drawing::FontStyle::Bold));
            this->titleLabel->Location = System::Drawing::Point(140, 32);
            this->titleLabel->Name = L"titleLabel";
            this->titleLabel->Size = System::Drawing::Size(453, 63);
            this->titleLabel->TabIndex = 0;
            this->titleLabel->Text = L"DUCK DUCK GO";
            //
            // MyForm
            //
            this->BackgroundImage = Image::FromFile("WhatsApp Image 2024-06-02 at 5.04.51 PM.jpeg");
             this->BackgroundImageLayout = ImageLayout::Stretch;
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(747, 579);
            this->Controls->Add(this->titleLabel);
            this->Controls->Add(this->comboBox1);
            this->Controls->Add(this->searchButton);
            this->Controls->Add(this->resultsListBox);
            this->Name = L"MyForm";
            this->Text = L"Search Engine";
            this->ResumeLayout(false);
            this->PerformLayout();

        }

#pragma endregion
        // pointer to the search engine object
        searchengine* engine;
    private: System::Void searchButton_Click(System::Object^ sender, System::EventArgs^ e) {



        // get the search query from the searchTextBox
        String^ query = comboBox1->Text;
       
        this->comboBox1->Items->Add(query);
    
        // convert the query from System::String^ to std::string
        std::string q = msclr::interop::marshal_as<std::string>(query);

        // create a new search engine object only if the query is not a path
        if (!engine->isQuery(q)) {
                engine = new searchengine("path", q);

                // execute search engine's search function
                engine->search();

                // clear the previous search results in the resultsListBox
                resultsListBox->Items->Clear();

                // get the list of matching files from the search engine
                const vector<std::string>& matchfile = engine->getbackfilename();
                if (matchfile.empty()) {
                    resultsListBox->Items->Add("no relevant files found");
                }
                else {
                    // add each matching file to the resultsListBox
                    for (const string& file : matchfile) {
                        // convert the file path from std::string to System::String^
                        String^ fileStr = gcnew String(file.c_str());
                        // add the file path to the resultsListBox
                        resultsListBox->Items->Add(fileStr);

                    }
                }

        }
        else {
            engine = new searchengine("path", q);

            // execute search engine's search function
            engine->search();

            // clear the previous search results in the resultsListBox
            resultsListBox->Items->Clear();

            // get the list of matching files from the search engine
            const vector<pair<std::string, int>>& matchfile = engine->getmatchingfiles();
            if (matchfile.empty()) {
                resultsListBox->Items->Add("no relevant files found");
            }
            else {
                // add each matching file to the resultsListBox
                for (const auto& file : matchfile) {

                    // convert the file path from std::string to System::String^
                    String^ fileStr = gcnew String(file.first.c_str());
                    // add the file path to the resultsListBox
                    resultsListBox->Items->Add(fileStr);

                }

            }
        }

    }

           //open new window when a specific file is selected in result box
                      //openedfile shows the content of selected file
    private: System::Void resultsListBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
        if (resultsListBox->SelectedIndex != -1) {
            //converting string from selected file to String^
            String^ selectedFile = resultsListBox->SelectedItem->ToString();
            //string of selected file as a path varriable
            std::string filePath = msclr::interop::marshal_as<std::string>(selectedFile);

            if (engine) {
                //if object of search engine is created it checks its file content at specified path and converts into string
                string content = engine->getfilecontent(filePath);
                //content of file from stringis converted to String^
                String^ fileContent = gcnew String(content.c_str());
                //passing that conent into the content box of new window
                FileContentForm^ contentForm = gcnew FileContentForm(fileContent);
                //displays the content form
                contentForm->Show();
            }
        }
    }

    };
}

