using System;
using System.Drawing;
using System.Windows.Forms;

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

            ShowPopup();
            // Timer (25 seconds)
            //timer = new System.Windows.Forms.Timer();
            //timer.Interval = 25000; // 25 seconds
            //timer.Tick += Timer_Tick;
            //timer.Start();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            ShowPopup();
        }

        private void ShowPopup()
        {
            foreach (Screen screen in Screen.AllScreens)
            {
                PopupForm popup = new PopupForm();

                // Manually position it to center of each screen
                popup.StartPosition = FormStartPosition.Manual;

                popup.Left = screen.Bounds.Left +
                             (screen.Bounds.Width - popup.Width) / 2;

                popup.Top = screen.Bounds.Top +
                            (screen.Bounds.Height - popup.Height) / 2;

                popup.Show();
            }
        }

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
            timer.Stop();
            Application.Exit();
        }
    }
}