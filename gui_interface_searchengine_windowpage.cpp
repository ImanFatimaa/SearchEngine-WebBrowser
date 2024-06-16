#pragma once

namespace gui {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class FileContentForm : public System::Windows::Forms::Form
    {
    public:
        FileContentForm(String^ fileContent)
        {
            InitializeComponent();
            fileContentTextBox->Text = fileContent;
        }

    protected:
        ~FileContentForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::TextBox^ fileContentTextBox;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->fileContentTextBox = (gcnew System::Windows::Forms::TextBox());
            this->SuspendLayout();
            // 
            // fileContentTextBox
            // 
            this->fileContentTextBox->Font = (gcnew System::Drawing::Font(L"Default", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->fileContentTextBox->Dock = System::Windows::Forms::DockStyle::Fill;
            this->fileContentTextBox->BackColor = System::Drawing::Color::Beige;
            this->fileContentTextBox->Multiline = true;
            this->fileContentTextBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
            this->fileContentTextBox->Location = System::Drawing::Point(0, 0);
            this->fileContentTextBox->Name = L"fileContentTextBox";
            this->fileContentTextBox->Size = System::Drawing::Size(800, 600);
            this->fileContentTextBox->TabIndex = 0;
            // 
            // FileContentForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;

            this->ClientSize = System::Drawing::Size(800, 600);
            this->Controls->Add(this->fileContentTextBox);
            this->Name = L"FileContentForm";
            this->Text = L"File Content";
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion
    };
}
