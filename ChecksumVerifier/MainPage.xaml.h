//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace ChecksumVerifier
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		void FileBrowseClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void GenerateChecksums(Windows::Storage::StorageFile^ file);
		void md5CheckboxClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
