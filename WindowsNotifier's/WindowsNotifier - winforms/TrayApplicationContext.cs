using Microsoft.Toolkit.Uwp.Notifications;
using System;
using System.Diagnostics;
using System.Drawing;
using System.Reflection.Metadata;
using System.Text.Json;
using System.Windows.Forms;
using Websocket.Client;


namespace WindowsNotifier
{
    public class TrayApplicationContext : ApplicationContext
    {
        private NotifyIcon trayIcon;
        private System.Windows.Forms.Timer timer;

        public TrayApplicationContext()
        {
            // Context menu
            var contextMenu = new ContextMenuStrip();
            contextMenu.Items.Add("Status", null, OnStatusClicked);
            contextMenu.Items.Add("Reconnect", null, OnReconnectClicked);
            contextMenu.Items.Add("Exit", null, OnExitClicked);

            // Tray Icon
            trayIcon = new NotifyIcon()
            {
                Icon = SystemIcons.Application,
                ContextMenuStrip = contextMenu,
                Visible = true,
                Text = "Tray Popup App"
            };

            PopupForm.ShowPopupForm();
            //ConnectToServer();
        }

        private async void ConnectToServer()
        {
            var url = new Uri("URL");

            var client = new WebsocketClient(url);
            client.ReconnectTimeout = TimeSpan.FromSeconds(10);
            client.ReconnectionHappened.Subscribe(info => Debug.WriteLine($"Reconnection happened, type: {info.Type}"));
            client.ErrorReconnectTimeout = null;

            client.MessageReceived.Subscribe(msg => MessageParser(msg.Text));
            await client.Start();

            if(client.IsRunning)
            {
                client.Send(JsonSerializer.Serialize(new { from = "DESKTOP" }));
            }
        }

        private void MessageParser(string? msg)
        {
            if(string.IsNullOrWhiteSpace(msg))
            {
                return;
            }

            var data = JsonSerializer.Deserialize<Data>(msg);
            
          if(data != null && data.currentValue <= 120 && !PopupForm.IsVisible)
            {
                //Debug.WriteLine("Called " + data.currentValue);
                PopupForm.ShowPopupForm();
            }
        }

        // Timer (25 seconds)
        //timer = new System.Windows.Forms.Timer();
        //timer.Interval = 25000; // 25 seconds
        //timer.Tick += Timer_Tick;
        //timer.Start();
        //private void Timer_Tick(object sender, EventArgs e)
        //{
        //    PopupForm.ShowPopupForm();
        //}

        private void OnStatusClicked(object? sender, EventArgs e)
        {
            MessageBox.Show("Application is running.", "Status");
        }

        private void OnReconnectClicked(object? sender, EventArgs e)
        {
            MessageBox.Show("Reconnecting...", "Reconnect");
        }

        private void OnExitClicked(object? sender, EventArgs e)
        {
            trayIcon.Visible = false;
            Application.Exit();
        }
    }
}