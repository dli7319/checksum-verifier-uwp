//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <openssl/md5.h>

using namespace ChecksumVerifier;

using namespace concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Streams;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
}


void ChecksumVerifier::MainPage::FileBrowseClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	FileOpenPicker^ openPicker = ref new FileOpenPicker();
	openPicker->FileTypeFilter->Append("*");
	create_task(openPicker->PickSingleFileAsync()).then([this](StorageFile^ file)
	{
		if (file)
		{
			filePathText->Text = file->Name;
			GenerateChecksums(file);
		}
	});

}

void ChecksumVerifier::MainPage::GenerateChecksums(StorageFile^ file)
{
	//https://stackoverflow.com/questions/1220046/how-to-get-the-md5-hash-of-a-file-in-c
	/*int file_descript;
	unsigned long file_size;
	char* file_buffer;

	file_descript = open(file, O_RDONLY);
	if (file_descript < 0) exit(-1);

	file_size = get_size_by_fd(file_descript);
	printf("file size:\t%lu\n", file_size);

	file_buffer = mmap(0, file_size, PROT_READ, MAP_SHARED, file_descript, 0);
	MD5((unsigned char*)file_buffer, file_size, result);
	munmap(file_buffer, file_size);

	print_md5_sum(result);
	printf("  %s\n", argv[1]);

	md5Text->Text = result;*/


	if (!file) {
		return;
	}

	if (md5Checkbox->IsChecked->Value)
	{
		create_task(FileIO::ReadBufferAsync(file)).then([this, file](task<IBuffer^> task)
		{

			unsigned char result[MD5_DIGEST_LENGTH];
			try
			{
				IBuffer^ buffer = task.get();
				DataReader^ dataReader = DataReader::FromBuffer(buffer);
				unsigned char* byteArr = new unsigned char[buffer->Length];
				dataReader->ReadBytes(ArrayReference<unsigned char>(byteArr, buffer->Length));
				MD5(byteArr, buffer->Length, result);
				delete byteArr;
				delete dataReader;
				char charBuffer[2 * MD5_DIGEST_LENGTH + 1];
				for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
					sprintf_s(charBuffer + 2 * i, 3, "%02x", result[i]);
				}
				std::string s_str(charBuffer);
				std::wstring wid_str(s_str.begin(), s_str.end());
				const wchar_t* w_char = wid_str.c_str();
				String^ str = ref new String(w_char);
				md5Text->Text = str;

			}
			catch (COMException^ ex)
			{

			}
		});
	}
}


void ChecksumVerifier::MainPage::md5CheckboxClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	
}
