using System;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;
using FormsTimer = System.Windows.Forms.Timer;
using Microsoft.Toolkit.Uwp.Notifications;

namespace WindowsNotifier
{
    public class PopupForm : Form
    {
        private FormsTimer closeTimer;

        //public PopupForm(Screen screen)
        //{
        //    FormBorderStyle = FormBorderStyle.None;
        //    StartPosition = FormStartPosition.Manual;
        //    ShowInTaskbar = false;
        //    TopMost = true;

        //    BackColor = Color.Black;
        //Opacity = 0.8;

        // Full screen overlay for that monitor
        //Bounds = screen.Bounds;

        //Label label = new Label();
        //label.Text = "25+";
        //label.ForeColor = Color.White;
        //label.Font = new Font("Segoe UI", 72, FontStyle.Bold);
        //label.Dock = DockStyle.Fill;
        //label.TextAlign = ContentAlignment.MiddleCenter;

        //Controls.Add(label);

        // Auto close after 3 sec
        //closeTimer = new FormsTimer();
        //closeTimer.Interval = 3000;
        //closeTimer.Tick += (s, e) =>
        //{
        //    closeTimer.Stop();
        //    Close();
        //};
        //closeTimer.Start();
        //}
        public static bool IsVisible = false;

        public static void ShowPopupForm()
        {
            IsVisible = true;
            foreach (Screen screen in Screen.AllScreens)
            {
                PopupForm popup = new PopupForm();

                // Manually position it to center of each screen
                popup.StartPosition = FormStartPosition.Manual;

                popup.Left = screen.Bounds.Left +
                             (screen.Bounds.Width - popup.Width) / 2;

                popup.Top = screen.Bounds.Top +
                            (screen.Bounds.Height - popup.Height) / 2;

                popup.FormClosed += (sender, e) =>
                {
                    IsVisible = false;
                };

                popup.Init().Show();
            }

        }

        public PopupForm Init()
        {
            FormBorderStyle = FormBorderStyle.None;
            StartPosition = FormStartPosition.CenterScreen;
            TopMost = true;
            ShowInTaskbar = false;

            BackColor = Color.Black;
            Opacity = 0.8; // Translucent

            Width = 800;
            Height = 200;

            Label label = new Label();
            label.Text = "Someone is here!";
            label.ForeColor = Color.White;
            label.Font = new Font("Segoe UI", 40, FontStyle.Bold);
            label.AutoSize = true;

            label.Left = (Width - label.Width) / 4;
            label.Top = (Height - label.Height) / 3;
            label.Anchor = AnchorStyles.None;


            Controls.Add(label);

            // Auto close after 3 seconds
            closeTimer = new FormsTimer();
            closeTimer.Interval = 3000;
            closeTimer.Tick += (s, e) =>
            {
                closeTimer.Stop();
                //this.Close();
            };
            closeTimer.Start();

            return this;
        }
    }
}