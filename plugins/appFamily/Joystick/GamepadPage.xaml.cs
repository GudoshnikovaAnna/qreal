using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Input;

// Документацию по шаблону элемента "Пустая страница" см. по адресу http://go.microsoft.com/fwlink/?LinkId=391641

namespace GamepadSemester
{
    /// <summary>
    /// Пустая страница, которую можно использовать саму по себе или для перехода внутри фрейма.
    /// </summary>
    public sealed partial class GamepadPage : Page
    {
        public GamepadPage()
        {
            this.InitializeComponent();

            this.NavigationCacheMode = NavigationCacheMode.Required;
        }

        /// <summary>
        /// Вызывается перед отображением этой страницы во фрейме.
        /// </summary>
        /// <param name="e">Данные события, описывающие, каким образом была достигнута эта страница.
        /// Этот параметр обычно используется для настройки страницы.</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {            
            ChangeButtonsAmount(Mediator.getButtonsAmount());
            ErrorBlock.Text = "";
        }

        private void TurnPage(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(SettingsPage), ButtonsPanel.Children.Count);
        }

        private void ButtonPressed(object sender, RoutedEventArgs e)
        {
            Button pressedButton = (Button)sender;

            Mediator.ButtonPressed((int)pressedButton.Content);
        }

        public void ChangeButtonsAmount(int amount)
        {
            ButtonsPanel.Children.Clear();

            for (int i = 0; i < amount; i++)
            {
                TextBlock tempTextBlock = new TextBlock();
                Button tempButton = new Button();
                StackPanel tempPanel = new StackPanel();

                tempTextBlock.Text = (i + 1).ToString();
                tempTextBlock.TextAlignment = TextAlignment.Center;
                tempTextBlock.Width = tempButton.Width;

                tempButton.Name = "AdditionalButton";
                tempButton.Template = ButtonTemplate;
                tempButton.Content = i + 1;
                tempButton.Click += ButtonPressed;

                tempPanel.Children.Add(tempTextBlock);
                tempPanel.Children.Add(tempButton);
                tempPanel.Width = tempButton.Width;

                ButtonsPanel.Children.Add(tempPanel);
                ButtonsPanel.Width += tempButton.Width;
            }
        }

        private void dPadPressed(object sender, PointerRoutedEventArgs e)
        {
            Image dPad = (Image)sender;
            PointerPoint point = e.GetCurrentPoint(dPad);

            Mediator.DPadPressed(point, dPad.Name);
        }

        private void dPadReleased(object sender, PointerRoutedEventArgs e)
        {
            Image dPad = (Image)sender;

            Mediator.DPadReleased(dPad.Name);
        }
    }
}
