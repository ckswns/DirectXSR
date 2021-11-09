
namespace NPK_AnimationTool
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openFolderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAnimationsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.label_frameCount = new System.Windows.Forms.Label();
            this.button_delete = new System.Windows.Forms.Button();
            this.button_change = new System.Windows.Forms.Button();
            this.lable_CurrentAnim = new System.Windows.Forms.Label();
            this.button_pause = new System.Windows.Forms.Button();
            this.button_stop = new System.Windows.Forms.Button();
            this.button_play = new System.Windows.Forms.Button();
            this.textBox_name = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.textBox_frameTime = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.checkBox_loop = new System.Windows.Forms.CheckBox();
            this.button_createAnim = new System.Windows.Forms.Button();
            this.textBox_centerY = new System.Windows.Forms.TextBox();
            this.textBox_centerX = new System.Windows.Forms.TextBox();
            this.textBox_endFrame = new System.Windows.Forms.TextBox();
            this.textBox_startFrame = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.splitContainer3 = new System.Windows.Forms.SplitContainer();
            this.previewPanel = new System.Windows.Forms.Panel();
            this.button_frameChange = new System.Windows.Forms.Button();
            this.button_frameDelete = new System.Windows.Forms.Button();
            this.button_frameInsert = new System.Windows.Forms.Button();
            this.label10 = new System.Windows.Forms.Label();
            this.textBox_frameIndex = new System.Windows.Forms.TextBox();
            this.textBox_frameEvent = new System.Windows.Forms.TextBox();
            this.textBox_selectFrameTime = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.pictureBox_frame = new System.Windows.Forms.PictureBox();
            this.label7 = new System.Windows.Forms.Label();
            this.splitContainer4 = new System.Windows.Forms.SplitContainer();
            this.listView_Frame = new System.Windows.Forms.ListView();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.spriteListView = new System.Windows.Forms.ListView();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.listView_animation = new System.Windows.Forms.ListView();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).BeginInit();
            this.splitContainer3.Panel1.SuspendLayout();
            this.splitContainer3.Panel2.SuspendLayout();
            this.splitContainer3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_frame)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer4)).BeginInit();
            this.splitContainer4.Panel1.SuspendLayout();
            this.splitContainer4.Panel2.SuspendLayout();
            this.splitContainer4.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.GripMargin = new System.Windows.Forms.Padding(2, 2, 0, 2);
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(11, 4, 0, 4);
            this.menuStrip1.Size = new System.Drawing.Size(1729, 48);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openFolderToolStripMenuItem,
            this.saveAnimationsToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(72, 40);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // openFolderToolStripMenuItem
            // 
            this.openFolderToolStripMenuItem.Name = "openFolderToolStripMenuItem";
            this.openFolderToolStripMenuItem.Size = new System.Drawing.Size(328, 44);
            this.openFolderToolStripMenuItem.Text = "Open Folder";
            this.openFolderToolStripMenuItem.Click += new System.EventHandler(this.openFolderToolStripMenuItem_Click);
            // 
            // saveAnimationsToolStripMenuItem
            // 
            this.saveAnimationsToolStripMenuItem.Name = "saveAnimationsToolStripMenuItem";
            this.saveAnimationsToolStripMenuItem.Size = new System.Drawing.Size(328, 44);
            this.saveAnimationsToolStripMenuItem.Text = "Save Animations";
            this.saveAnimationsToolStripMenuItem.Click += new System.EventHandler(this.saveAnimationsToolStripMenuItem_Click);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 48);
            this.splitContainer1.Margin = new System.Windows.Forms.Padding(6);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.splitContainer2);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.splitContainer1.Panel2.Controls.Add(this.splitContainer4);
            this.splitContainer1.Size = new System.Drawing.Size(1729, 1052);
            this.splitContainer1.SplitterDistance = 538;
            this.splitContainer1.SplitterWidth = 16;
            this.splitContainer1.TabIndex = 1;
            this.splitContainer1.TabStop = false;
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Margin = new System.Windows.Forms.Padding(6);
            this.splitContainer2.Name = "splitContainer2";
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.splitContainer2.Panel1.Controls.Add(this.label_frameCount);
            this.splitContainer2.Panel1.Controls.Add(this.button_delete);
            this.splitContainer2.Panel1.Controls.Add(this.button_change);
            this.splitContainer2.Panel1.Controls.Add(this.lable_CurrentAnim);
            this.splitContainer2.Panel1.Controls.Add(this.button_pause);
            this.splitContainer2.Panel1.Controls.Add(this.button_stop);
            this.splitContainer2.Panel1.Controls.Add(this.button_play);
            this.splitContainer2.Panel1.Controls.Add(this.textBox_name);
            this.splitContainer2.Panel1.Controls.Add(this.label6);
            this.splitContainer2.Panel1.Controls.Add(this.textBox_frameTime);
            this.splitContainer2.Panel1.Controls.Add(this.label5);
            this.splitContainer2.Panel1.Controls.Add(this.checkBox_loop);
            this.splitContainer2.Panel1.Controls.Add(this.button_createAnim);
            this.splitContainer2.Panel1.Controls.Add(this.textBox_centerY);
            this.splitContainer2.Panel1.Controls.Add(this.textBox_centerX);
            this.splitContainer2.Panel1.Controls.Add(this.textBox_endFrame);
            this.splitContainer2.Panel1.Controls.Add(this.textBox_startFrame);
            this.splitContainer2.Panel1.Controls.Add(this.label4);
            this.splitContainer2.Panel1.Controls.Add(this.label3);
            this.splitContainer2.Panel1.Controls.Add(this.label2);
            this.splitContainer2.Panel1.Controls.Add(this.label1);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.BackColor = System.Drawing.SystemColors.Control;
            this.splitContainer2.Panel2.Controls.Add(this.splitContainer3);
            this.splitContainer2.Size = new System.Drawing.Size(1729, 538);
            this.splitContainer2.SplitterDistance = 316;
            this.splitContainer2.SplitterWidth = 15;
            this.splitContainer2.TabIndex = 0;
            // 
            // label_frameCount
            // 
            this.label_frameCount.AutoSize = true;
            this.label_frameCount.Location = new System.Drawing.Point(27, 493);
            this.label_frameCount.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label_frameCount.Name = "label_frameCount";
            this.label_frameCount.Size = new System.Drawing.Size(158, 24);
            this.label_frameCount.TabIndex = 20;
            this.label_frameCount.Text = "Frame Count :";
            // 
            // button_delete
            // 
            this.button_delete.Location = new System.Drawing.Point(108, 350);
            this.button_delete.Margin = new System.Windows.Forms.Padding(6);
            this.button_delete.Name = "button_delete";
            this.button_delete.Size = new System.Drawing.Size(100, 35);
            this.button_delete.TabIndex = 19;
            this.button_delete.Text = "delete";
            this.button_delete.UseVisualStyleBackColor = true;
            this.button_delete.Click += new System.EventHandler(this.button_delete_Click);
            // 
            // button_change
            // 
            this.button_change.Location = new System.Drawing.Point(208, 350);
            this.button_change.Margin = new System.Windows.Forms.Padding(6);
            this.button_change.Name = "button_change";
            this.button_change.Size = new System.Drawing.Size(100, 35);
            this.button_change.TabIndex = 18;
            this.button_change.Text = "Change";
            this.button_change.UseVisualStyleBackColor = true;
            this.button_change.Click += new System.EventHandler(this.button_change_Click);
            // 
            // lable_CurrentAnim
            // 
            this.lable_CurrentAnim.AutoSize = true;
            this.lable_CurrentAnim.Location = new System.Drawing.Point(22, 451);
            this.lable_CurrentAnim.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.lable_CurrentAnim.Name = "lable_CurrentAnim";
            this.lable_CurrentAnim.Size = new System.Drawing.Size(83, 24);
            this.lable_CurrentAnim.TabIndex = 17;
            this.lable_CurrentAnim.Text = "Anim : ";
            // 
            // button_pause
            // 
            this.button_pause.Location = new System.Drawing.Point(108, 397);
            this.button_pause.Margin = new System.Windows.Forms.Padding(6);
            this.button_pause.Name = "button_pause";
            this.button_pause.Size = new System.Drawing.Size(100, 35);
            this.button_pause.TabIndex = 16;
            this.button_pause.Text = "pause";
            this.button_pause.UseVisualStyleBackColor = true;
            this.button_pause.Click += new System.EventHandler(this.button_pause_Click);
            // 
            // button_stop
            // 
            this.button_stop.Location = new System.Drawing.Point(208, 397);
            this.button_stop.Margin = new System.Windows.Forms.Padding(6);
            this.button_stop.Name = "button_stop";
            this.button_stop.Size = new System.Drawing.Size(100, 35);
            this.button_stop.TabIndex = 15;
            this.button_stop.Text = "Stop";
            this.button_stop.UseVisualStyleBackColor = true;
            this.button_stop.Click += new System.EventHandler(this.button_stop_Click);
            // 
            // button_play
            // 
            this.button_play.Location = new System.Drawing.Point(6, 397);
            this.button_play.Margin = new System.Windows.Forms.Padding(6);
            this.button_play.Name = "button_play";
            this.button_play.Size = new System.Drawing.Size(100, 35);
            this.button_play.TabIndex = 14;
            this.button_play.Text = "Play";
            this.button_play.UseVisualStyleBackColor = true;
            this.button_play.Click += new System.EventHandler(this.button_play_Click);
            // 
            // textBox_name
            // 
            this.textBox_name.Location = new System.Drawing.Point(196, 254);
            this.textBox_name.Margin = new System.Windows.Forms.Padding(6);
            this.textBox_name.Name = "textBox_name";
            this.textBox_name.Size = new System.Drawing.Size(97, 35);
            this.textBox_name.TabIndex = 6;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(22, 262);
            this.label6.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(67, 24);
            this.label6.TabIndex = 12;
            this.label6.Text = "Name";
            // 
            // textBox_frameTime
            // 
            this.textBox_frameTime.Location = new System.Drawing.Point(196, 207);
            this.textBox_frameTime.Margin = new System.Windows.Forms.Padding(6);
            this.textBox_frameTime.Name = "textBox_frameTime";
            this.textBox_frameTime.Size = new System.Drawing.Size(97, 35);
            this.textBox_frameTime.TabIndex = 5;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Gulim", 7F);
            this.label5.Location = new System.Drawing.Point(22, 214);
            this.label5.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(163, 19);
            this.label5.TabIndex = 10;
            this.label5.Text = "Default Frame Time";
            // 
            // checkBox_loop
            // 
            this.checkBox_loop.AutoSize = true;
            this.checkBox_loop.Location = new System.Drawing.Point(26, 311);
            this.checkBox_loop.Margin = new System.Windows.Forms.Padding(6);
            this.checkBox_loop.Name = "checkBox_loop";
            this.checkBox_loop.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.checkBox_loop.Size = new System.Drawing.Size(96, 28);
            this.checkBox_loop.TabIndex = 7;
            this.checkBox_loop.Text = "Loop";
            this.checkBox_loop.UseVisualStyleBackColor = true;
            // 
            // button_createAnim
            // 
            this.button_createAnim.Location = new System.Drawing.Point(6, 350);
            this.button_createAnim.Margin = new System.Windows.Forms.Padding(6);
            this.button_createAnim.Name = "button_createAnim";
            this.button_createAnim.Size = new System.Drawing.Size(100, 35);
            this.button_createAnim.TabIndex = 8;
            this.button_createAnim.Text = "Create Animation";
            this.button_createAnim.UseVisualStyleBackColor = true;
            this.button_createAnim.Click += new System.EventHandler(this.button_createAnim_Click);
            // 
            // textBox_centerY
            // 
            this.textBox_centerY.Location = new System.Drawing.Point(196, 159);
            this.textBox_centerY.Margin = new System.Windows.Forms.Padding(6);
            this.textBox_centerY.Name = "textBox_centerY";
            this.textBox_centerY.Size = new System.Drawing.Size(97, 35);
            this.textBox_centerY.TabIndex = 4;
            // 
            // textBox_centerX
            // 
            this.textBox_centerX.Location = new System.Drawing.Point(196, 112);
            this.textBox_centerX.Margin = new System.Windows.Forms.Padding(6);
            this.textBox_centerX.Name = "textBox_centerX";
            this.textBox_centerX.Size = new System.Drawing.Size(97, 35);
            this.textBox_centerX.TabIndex = 3;
            // 
            // textBox_endFrame
            // 
            this.textBox_endFrame.Location = new System.Drawing.Point(196, 63);
            this.textBox_endFrame.Margin = new System.Windows.Forms.Padding(6);
            this.textBox_endFrame.Name = "textBox_endFrame";
            this.textBox_endFrame.Size = new System.Drawing.Size(97, 35);
            this.textBox_endFrame.TabIndex = 2;
            // 
            // textBox_startFrame
            // 
            this.textBox_startFrame.Location = new System.Drawing.Point(196, 16);
            this.textBox_startFrame.Margin = new System.Windows.Forms.Padding(6);
            this.textBox_startFrame.Name = "textBox_startFrame";
            this.textBox_startFrame.Size = new System.Drawing.Size(97, 35);
            this.textBox_startFrame.TabIndex = 1;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(22, 166);
            this.label4.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(93, 24);
            this.label4.TabIndex = 3;
            this.label4.Text = "CenterY";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(22, 118);
            this.label3.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(101, 24);
            this.label3.TabIndex = 2;
            this.label3.Text = "Center X";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(22, 70);
            this.label2.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(115, 24);
            this.label2.TabIndex = 1;
            this.label2.Text = "End frame";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(22, 22);
            this.label1.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(126, 24);
            this.label1.TabIndex = 0;
            this.label1.Text = "Start frame";
            // 
            // splitContainer3
            // 
            this.splitContainer3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer3.Location = new System.Drawing.Point(0, 0);
            this.splitContainer3.Name = "splitContainer3";
            // 
            // splitContainer3.Panel1
            // 
            this.splitContainer3.Panel1.Controls.Add(this.previewPanel);
            // 
            // splitContainer3.Panel2
            // 
            this.splitContainer3.Panel2.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.splitContainer3.Panel2.Controls.Add(this.button_frameChange);
            this.splitContainer3.Panel2.Controls.Add(this.button_frameDelete);
            this.splitContainer3.Panel2.Controls.Add(this.button_frameInsert);
            this.splitContainer3.Panel2.Controls.Add(this.label10);
            this.splitContainer3.Panel2.Controls.Add(this.textBox_frameIndex);
            this.splitContainer3.Panel2.Controls.Add(this.textBox_frameEvent);
            this.splitContainer3.Panel2.Controls.Add(this.textBox_selectFrameTime);
            this.splitContainer3.Panel2.Controls.Add(this.label9);
            this.splitContainer3.Panel2.Controls.Add(this.label8);
            this.splitContainer3.Panel2.Controls.Add(this.pictureBox_frame);
            this.splitContainer3.Panel2.Controls.Add(this.label7);
            this.splitContainer3.Size = new System.Drawing.Size(1398, 538);
            this.splitContainer3.SplitterDistance = 1082;
            this.splitContainer3.SplitterWidth = 8;
            this.splitContainer3.TabIndex = 1;
            // 
            // previewPanel
            // 
            this.previewPanel.AutoScroll = true;
            this.previewPanel.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.previewPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.previewPanel.Location = new System.Drawing.Point(0, 0);
            this.previewPanel.Margin = new System.Windows.Forms.Padding(0);
            this.previewPanel.Name = "previewPanel";
            this.previewPanel.Size = new System.Drawing.Size(1082, 538);
            this.previewPanel.TabIndex = 0;
            // 
            // button_frameChange
            // 
            this.button_frameChange.Location = new System.Drawing.Point(35, 397);
            this.button_frameChange.Margin = new System.Windows.Forms.Padding(6);
            this.button_frameChange.Name = "button_frameChange";
            this.button_frameChange.Size = new System.Drawing.Size(100, 35);
            this.button_frameChange.TabIndex = 26;
            this.button_frameChange.Text = "change";
            this.button_frameChange.UseVisualStyleBackColor = true;
            this.button_frameChange.Click += new System.EventHandler(this.button_frameChange_Click);
            // 
            // button_frameDelete
            // 
            this.button_frameDelete.Location = new System.Drawing.Point(199, 350);
            this.button_frameDelete.Margin = new System.Windows.Forms.Padding(6);
            this.button_frameDelete.Name = "button_frameDelete";
            this.button_frameDelete.Size = new System.Drawing.Size(100, 35);
            this.button_frameDelete.TabIndex = 25;
            this.button_frameDelete.Text = "delete";
            this.button_frameDelete.UseVisualStyleBackColor = true;
            this.button_frameDelete.Click += new System.EventHandler(this.button_frameDelete_Click);
            // 
            // button_frameInsert
            // 
            this.button_frameInsert.Location = new System.Drawing.Point(35, 350);
            this.button_frameInsert.Margin = new System.Windows.Forms.Padding(6);
            this.button_frameInsert.Name = "button_frameInsert";
            this.button_frameInsert.Size = new System.Drawing.Size(100, 35);
            this.button_frameInsert.TabIndex = 21;
            this.button_frameInsert.Text = "Insert";
            this.button_frameInsert.UseVisualStyleBackColor = true;
            this.button_frameInsert.Click += new System.EventHandler(this.button_frameInsert_Click);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(31, 311);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(135, 24);
            this.label10.TabIndex = 24;
            this.label10.Text = "Frame Index";
            // 
            // textBox_frameIndex
            // 
            this.textBox_frameIndex.Location = new System.Drawing.Point(202, 301);
            this.textBox_frameIndex.Margin = new System.Windows.Forms.Padding(6);
            this.textBox_frameIndex.Name = "textBox_frameIndex";
            this.textBox_frameIndex.Size = new System.Drawing.Size(97, 35);
            this.textBox_frameIndex.TabIndex = 10;
            // 
            // textBox_frameEvent
            // 
            this.textBox_frameEvent.Location = new System.Drawing.Point(103, 254);
            this.textBox_frameEvent.Margin = new System.Windows.Forms.Padding(6);
            this.textBox_frameEvent.Name = "textBox_frameEvent";
            this.textBox_frameEvent.Size = new System.Drawing.Size(196, 35);
            this.textBox_frameEvent.TabIndex = 9;
            // 
            // textBox_selectFrameTime
            // 
            this.textBox_selectFrameTime.Location = new System.Drawing.Point(202, 16);
            this.textBox_selectFrameTime.Margin = new System.Windows.Forms.Padding(6);
            this.textBox_selectFrameTime.Name = "textBox_selectFrameTime";
            this.textBox_selectFrameTime.Size = new System.Drawing.Size(97, 35);
            this.textBox_selectFrameTime.TabIndex = 8;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(31, 257);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(69, 24);
            this.label9.TabIndex = 3;
            this.label9.Text = "Event";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(31, 70);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(69, 24);
            this.label8.TabIndex = 2;
            this.label8.Text = "Image";
            // 
            // pictureBox_frame
            // 
            this.pictureBox_frame.Location = new System.Drawing.Point(139, 63);
            this.pictureBox_frame.Name = "pictureBox_frame";
            this.pictureBox_frame.Size = new System.Drawing.Size(160, 141);
            this.pictureBox_frame.TabIndex = 1;
            this.pictureBox_frame.TabStop = false;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(31, 22);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(130, 24);
            this.label7.TabIndex = 0;
            this.label7.Text = "Frame TIme";
            // 
            // splitContainer4
            // 
            this.splitContainer4.BackColor = System.Drawing.SystemColors.Control;
            this.splitContainer4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer4.Location = new System.Drawing.Point(0, 0);
            this.splitContainer4.Name = "splitContainer4";
            this.splitContainer4.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer4.Panel1
            // 
            this.splitContainer4.Panel1.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.splitContainer4.Panel1.Controls.Add(this.listView_Frame);
            // 
            // splitContainer4.Panel2
            // 
            this.splitContainer4.Panel2.Controls.Add(this.tabControl1);
            this.splitContainer4.Size = new System.Drawing.Size(1729, 498);
            this.splitContainer4.SplitterDistance = 223;
            this.splitContainer4.SplitterWidth = 8;
            this.splitContainer4.TabIndex = 0;
            // 
            // listView_Frame
            // 
            this.listView_Frame.Alignment = System.Windows.Forms.ListViewAlignment.Left;
            this.listView_Frame.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.listView_Frame.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listView_Frame.HideSelection = false;
            this.listView_Frame.Location = new System.Drawing.Point(0, 0);
            this.listView_Frame.Name = "listView_Frame";
            this.listView_Frame.Size = new System.Drawing.Size(1729, 223);
            this.listView_Frame.TabIndex = 0;
            this.listView_Frame.UseCompatibleStateImageBehavior = false;
            this.listView_Frame.SelectedIndexChanged += new System.EventHandler(this.listView_Frame_SelectedIndexChanged);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Margin = new System.Windows.Forms.Padding(6);
            this.tabControl1.Multiline = true;
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(1729, 267);
            this.tabControl1.TabIndex = 1;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.spriteListView);
            this.tabPage1.Location = new System.Drawing.Point(8, 39);
            this.tabPage1.Margin = new System.Windows.Forms.Padding(6);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(6);
            this.tabPage1.Size = new System.Drawing.Size(1713, 220);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "images";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // spriteListView
            // 
            this.spriteListView.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.spriteListView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.spriteListView.HideSelection = false;
            this.spriteListView.Location = new System.Drawing.Point(6, 6);
            this.spriteListView.Margin = new System.Windows.Forms.Padding(0);
            this.spriteListView.Name = "spriteListView";
            this.spriteListView.Size = new System.Drawing.Size(1701, 208);
            this.spriteListView.TabIndex = 0;
            this.spriteListView.UseCompatibleStateImageBehavior = false;
            this.spriteListView.SelectedIndexChanged += new System.EventHandler(this.spriteListView_SelectedIndexChanged);
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.listView_animation);
            this.tabPage2.Location = new System.Drawing.Point(8, 39);
            this.tabPage2.Margin = new System.Windows.Forms.Padding(6);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(6);
            this.tabPage2.Size = new System.Drawing.Size(1713, 220);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "animations";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // listView_animation
            // 
            this.listView_animation.Alignment = System.Windows.Forms.ListViewAlignment.Left;
            this.listView_animation.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.listView_animation.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listView_animation.HideSelection = false;
            this.listView_animation.Location = new System.Drawing.Point(6, 6);
            this.listView_animation.Margin = new System.Windows.Forms.Padding(0);
            this.listView_animation.Name = "listView_animation";
            this.listView_animation.Size = new System.Drawing.Size(1701, 208);
            this.listView_animation.TabIndex = 0;
            this.listView_animation.UseCompatibleStateImageBehavior = false;
            this.listView_animation.SelectedIndexChanged += new System.EventHandler(this.listView_animation_SelectedIndexChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(13F, 24F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1729, 1100);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(6);
            this.Name = "Form1";
            this.Text = "Form1";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel1.PerformLayout();
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            this.splitContainer3.Panel1.ResumeLayout(false);
            this.splitContainer3.Panel2.ResumeLayout(false);
            this.splitContainer3.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).EndInit();
            this.splitContainer3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_frame)).EndInit();
            this.splitContainer4.Panel1.ResumeLayout(false);
            this.splitContainer4.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer4)).EndInit();
            this.splitContainer4.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openFolderToolStripMenuItem;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.ListView spriteListView;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.ListView listView_animation;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.Button button_delete;
        private System.Windows.Forms.Button button_change;
        private System.Windows.Forms.Label lable_CurrentAnim;
        private System.Windows.Forms.Button button_pause;
        private System.Windows.Forms.Button button_stop;
        private System.Windows.Forms.Button button_play;
        private System.Windows.Forms.TextBox textBox_name;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox textBox_frameTime;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.CheckBox checkBox_loop;
        private System.Windows.Forms.Button button_createAnim;
        private System.Windows.Forms.TextBox textBox_centerY;
        private System.Windows.Forms.TextBox textBox_centerX;
        private System.Windows.Forms.TextBox textBox_endFrame;
        private System.Windows.Forms.TextBox textBox_startFrame;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel previewPanel;
        private System.Windows.Forms.SplitContainer splitContainer3;
        private System.Windows.Forms.SplitContainer splitContainer4;
        private System.Windows.Forms.ListView listView_Frame;
        private System.Windows.Forms.Label label_frameCount;
        private System.Windows.Forms.TextBox textBox_frameEvent;
        private System.Windows.Forms.TextBox textBox_selectFrameTime;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.PictureBox pictureBox_frame;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button button_frameDelete;
        private System.Windows.Forms.Button button_frameInsert;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBox_frameIndex;
        private System.Windows.Forms.Button button_frameChange;
        private System.Windows.Forms.ToolStripMenuItem saveAnimationsToolStripMenuItem;
    }
}

