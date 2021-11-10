using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace NPK_AnimationTool
{
    public partial class Form1 : Form
    {
        private List<Sprite> spriteList;
        private List<Animation> animationList;
        private int currentAnimationIndex;

        public static Brush whiteBrush;
        public static Pen redPen;
        BufferedGraphicsContext currentContext;
        public static BufferedGraphics myBuffer;
        public static Timer animationTimer;
        string currentFolderPath = "";
        int selectedImgIndex;

        public Form1()
        {
            InitializeComponent();
            spriteList = new List<Sprite>();
            animationList = new List<Animation>();
            currentContext = BufferedGraphicsManager.Current;
            myBuffer = currentContext.Allocate(previewPanel.CreateGraphics(), previewPanel.DisplayRectangle);
            currentAnimationIndex = -1;
            DoubleBuffered = true;
            animationTimer = new Timer();
            animationTimer.Tick += new EventHandler(PlayAnimationInterval);

            whiteBrush = new SolidBrush(Color.White);
            redPen = new Pen(new SolidBrush(Color.Red), 0.4f);
        }

        private void openFolderToolStripMenuItem_Click(object sender, EventArgs e)
        {
            spriteList.Clear();
            animationList.Clear();
            currentAnimationIndex = -1;
            animationTimer.Stop();
            myBuffer.Graphics.FillRectangle(whiteBrush, previewPanel.ClientRectangle);
            myBuffer.Render();

            listView_animation.Items.Clear();
            listView_Frame.Items.Clear();
            spriteListView.Items.Clear();

            FolderBrowserDialog dlg = new FolderBrowserDialog();
            dlg.RootFolder = Environment.SpecialFolder.MyComputer;
            dlg.SelectedPath = Environment.CurrentDirectory;

            string[] pattern = { "*.png" };

            if (dlg.ShowDialog() == DialogResult.OK)
            {
                ImageList imgList;
                string[] DataFileNM = pattern.SelectMany(patterns =>
                    Directory.GetFiles(dlg.SelectedPath, patterns)).ToArray();

                imgList = new ImageList();
                imgList.ImageSize = new Size(64, 64);

                for (int i = 0; i < DataFileNM.Length; i++)
                {
                    Image temp = Image.FromFile(DataFileNM[i]);
                    String str = DataFileNM[i];
                    String[] strs = str.Split('\\');

                    str = strs[strs.Length - 1];

                    imgList.Images.Add(i.ToString(), temp);
                    
                    Sprite spr = new Sprite(temp, str);

                    spriteList.Add(spr);
                }

                this.spriteListView.SmallImageList = imgList;
                this.spriteListView.LargeImageList = imgList;

                for (int i = 0; i < imgList.Images.Count; i++)
                {
                    String str = DataFileNM[i];
                    String[] strs = str.Split('\\');

                    str = strs[strs.Length - 1];

                    spriteListView.Items.Add(new ListViewItem(DataFileNM[i], i));
                    this.spriteListView.Items[i].Text = str;
                }

                this.Refresh();
            }

            currentFolderPath = dlg.SelectedPath;
            dlg.Dispose();

            Invalidate();
        }

        private void button_createAnim_Click(object sender, EventArgs e)
        {
            animationTimer.Stop();
            int startFrame = int.Parse(textBox_startFrame.Text);
            int endFrame = int.Parse(textBox_endFrame.Text);
            int centerX = int.Parse(textBox_centerX.Text);
            int centerY = int.Parse(textBox_centerY.Text);
            float frameTime = float.Parse(textBox_frameTime.Text);
            string name = textBox_name.Text;
            bool loop = checkBox_loop.Checked;

            for (int i = 0; i < animationList.Count; i++)
            {
                if (animationList[i].name == name)
                    return;
            }

            animationList.Add(new Animation(ref spriteList, name, loop, centerX, centerY, frameTime, startFrame, endFrame));
            currentAnimationIndex = animationList.Count - 1;

            if (listView_animation.LargeImageList != null)
            {
                listView_animation.LargeImageList.Images.Add(spriteList[startFrame].image);

                listView_animation.Items.Add(new ListViewItem(name, listView_animation.Items.Count));
                listView_animation.Items[listView_animation.Items.Count - 1].Text = name;
            }
            else
            {
                ImageList imageList = new ImageList();
                imageList.Images.Add(spriteList[startFrame].image);

                listView_animation.LargeImageList = imageList;
                listView_animation.LargeImageList.ImageSize = new Size(128, 128);
                listView_animation.Items.Add(new ListViewItem(name, listView_animation.Items.Count));
                listView_animation.Items[listView_animation.Items.Count - 1].Text = name;
            }

            ChangeCurrentAnimation(currentAnimationIndex);
        }

        private void button_play_Click(object sender, EventArgs e)
        {
            if (currentAnimationIndex == -1)
                return;

            animationTimer.Stop();
            animationTimer.Interval = 1;


            animationTimer.Start();
        }

        public void PlayAnimationInterval(object sender, System.EventArgs e)
        {
            int index = animationList[currentAnimationIndex].currentFrame;

            textBox_frameIndex.Text = index.ToString();

            if (animationList[currentAnimationIndex].spriteList[index].frameTime == 0)
                textBox_selectFrameTime.Text = animationList[currentAnimationIndex].frameTime.ToString();
            else
                textBox_selectFrameTime.Text = animationList[currentAnimationIndex].spriteList[index].frameTime.ToString();

            pictureBox_frame.Image = animationList[currentAnimationIndex].spriteList[index].image;
            textBox_frameEvent.Text = animationList[currentAnimationIndex].spriteList[index].eventStr;

            myBuffer.Graphics.FillRectangle(whiteBrush, previewPanel.ClientRectangle);
            myBuffer.Graphics.DrawLine(redPen, new Point(previewPanel.Left, animationList[currentAnimationIndex].centerY), new Point(previewPanel.Right, animationList[currentAnimationIndex].centerY));
            myBuffer.Graphics.DrawLine(redPen, new Point(animationList[currentAnimationIndex].centerX, previewPanel.Top), new Point(animationList[currentAnimationIndex].centerX, previewPanel.Bottom));
            animationList[currentAnimationIndex].Render();
            myBuffer.Render();
            Invalidate();
        }

        private void listView_animation_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listView_animation.SelectedItems.Count == 0)
                return;

            ChangeCurrentAnimation(listView_animation.SelectedItems[0].Index);
        }

        private void button_stop_Click(object sender, EventArgs e)
        {
            animationTimer.Stop();
            myBuffer.Graphics.FillRectangle(whiteBrush, previewPanel.ClientRectangle);
            myBuffer.Graphics.DrawLine(redPen, new Point(previewPanel.Left, animationList[currentAnimationIndex].centerY), new Point(previewPanel.Right, animationList[currentAnimationIndex].centerY));
            myBuffer.Graphics.DrawLine(redPen, new Point(animationList[currentAnimationIndex].centerX, previewPanel.Top), new Point(animationList[currentAnimationIndex].centerX, previewPanel.Bottom));
            animationList[currentAnimationIndex].Render(0);
            myBuffer.Render();
            Invalidate();
        }

        private void button_pause_Click(object sender, EventArgs e)
        {
            animationTimer.Stop();
        }

        private void button_change_Click(object sender, EventArgs e)
        {
            animationTimer.Stop();

            int startFrame = int.Parse(textBox_startFrame.Text);
            int endFrame = int.Parse(textBox_endFrame.Text);
            int centerX = int.Parse(textBox_centerX.Text);
            int centerY = int.Parse(textBox_centerY.Text);
            float frameTime = float.Parse(textBox_frameTime.Text);
            string name = textBox_name.Text;
            bool loop = checkBox_loop.Checked;

            animationList[currentAnimationIndex].centerX = centerX;
            animationList[currentAnimationIndex].centerY = centerY;
            animationList[currentAnimationIndex].frameTime = frameTime;
            animationList[currentAnimationIndex].name = name;
            animationList[currentAnimationIndex].loop = loop;

            myBuffer.Graphics.FillRectangle(whiteBrush, previewPanel.ClientRectangle);
            myBuffer.Graphics.DrawLine(redPen, new Point(previewPanel.Left, animationList[currentAnimationIndex].centerY), new Point(previewPanel.Right, animationList[currentAnimationIndex].centerY));
            myBuffer.Graphics.DrawLine(redPen, new Point(animationList[currentAnimationIndex].centerX, previewPanel.Top), new Point(animationList[currentAnimationIndex].centerX, previewPanel.Bottom));

            ChangeCurrentAnimation(currentAnimationIndex);
        }

        private void button_delete_Click(object sender, EventArgs e)
        {
            if (currentAnimationIndex == -1)
                return;

            animationList.RemoveAt(currentAnimationIndex);
            listView_animation.Items.RemoveAt(currentAnimationIndex);

            currentAnimationIndex = -1;
            myBuffer.Graphics.FillRectangle(whiteBrush, previewPanel.ClientRectangle);
            myBuffer.Render();
            Invalidate();
        }

        private void ChangeCurrentAnimation(int index)
        {
            animationTimer.Stop();

            currentAnimationIndex = index;

            lable_CurrentAnim.Text = "Anim : " + animationList[currentAnimationIndex].name;
            label_frameCount.Text = "Frame Count : " + animationList[currentAnimationIndex].spriteList.Count.ToString();

            //textBox_startFrame.Text = animationList[currentAnimationIndex].startFrame.ToString();
            //textBox_endFrame.Text = animationList[currentAnimationIndex].endFrame.ToString();
            textBox_centerX.Text = animationList[currentAnimationIndex].centerX.ToString();
            textBox_centerY.Text = animationList[currentAnimationIndex].centerY.ToString();
            textBox_frameTime.Text = animationList[currentAnimationIndex].frameTime.ToString();
            textBox_name.Text = animationList[currentAnimationIndex].name;
            checkBox_loop.Checked = animationList[currentAnimationIndex].loop;

            myBuffer.Graphics.FillRectangle(whiteBrush, previewPanel.ClientRectangle);
            myBuffer.Graphics.DrawLine(redPen, new Point(previewPanel.Left, animationList[currentAnimationIndex].centerY), new Point(previewPanel.Right, animationList[currentAnimationIndex].centerY));
            myBuffer.Graphics.DrawLine(redPen, new Point(animationList[currentAnimationIndex].centerX, previewPanel.Top), new Point(animationList[currentAnimationIndex].centerX, previewPanel.Bottom));
            animationList[currentAnimationIndex].Render(0);
            myBuffer.Render();

            listView_Frame.Items.Clear();
            
            if(listView_Frame.LargeImageList == null)
            {
                listView_Frame.LargeImageList = new ImageList();
            }

            listView_Frame.LargeImageList.Images.Clear();
            listView_Frame.LargeImageList.ImageSize = new Size(128, 128);

            for (int i = 0; i < animationList[currentAnimationIndex].spriteList.Count; i++)
            {
                listView_Frame.LargeImageList.Images.Add(animationList[currentAnimationIndex].spriteList[i].image);
                listView_Frame.Items.Add(i.ToString(), i);
            }

            Invalidate();
        }

        private void spriteListView_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (currentAnimationIndex == -1)
                return;

            if (spriteListView.SelectedItems.Count == 0)
                return;

            int index = spriteListView.SelectedItems[0].Index;

            textBox_frameIndex.Text = animationList[currentAnimationIndex].spriteList.Count.ToString();

            textBox_selectFrameTime.Text = animationList[currentAnimationIndex].frameTime.ToString();

            pictureBox_frame.Image = spriteList[index].image;
            textBox_frameEvent.Text = "";
            selectedImgIndex = index;

            Invalidate();
        }

        private void listView_Frame_SelectedIndexChanged(object sender, EventArgs e)
        {
            animationTimer.Stop();

            if(listView_Frame.SelectedItems.Count == 0)
                return;
            int index = listView_Frame.SelectedItems[0].Index;

            textBox_frameIndex.Text = index.ToString();

            if (animationList[currentAnimationIndex].spriteList[index].frameTime == 0)
                textBox_selectFrameTime.Text = animationList[currentAnimationIndex].frameTime.ToString();
            else
                textBox_selectFrameTime.Text = animationList[currentAnimationIndex].spriteList[index].frameTime.ToString();

            pictureBox_frame.Image = animationList[currentAnimationIndex].spriteList[index].image;
            textBox_frameEvent.Text = animationList[currentAnimationIndex].spriteList[index].eventStr;

            myBuffer.Graphics.FillRectangle(whiteBrush, previewPanel.ClientRectangle);
            myBuffer.Graphics.DrawLine(redPen, new Point(previewPanel.Left, animationList[currentAnimationIndex].centerY), new Point(previewPanel.Right, animationList[currentAnimationIndex].centerY));
            myBuffer.Graphics.DrawLine(redPen, new Point(animationList[currentAnimationIndex].centerX, previewPanel.Top), new Point(animationList[currentAnimationIndex].centerX, previewPanel.Bottom));
            animationList[currentAnimationIndex].Render(index);
            myBuffer.Render();

            Invalidate();
        }

        private void button_frameInsert_Click(object sender, EventArgs e)
        {
            int index = int.Parse(textBox_frameIndex.Text);

            Sprite sprite = new Sprite(spriteList[selectedImgIndex].image, spriteList[selectedImgIndex].fileName);

            sprite.frameTime = float.Parse(textBox_selectFrameTime.Text);
            sprite.eventStr = textBox_frameEvent.Text;

            animationList[currentAnimationIndex].spriteList.Insert(index, sprite);

            ChangeCurrentAnimation(currentAnimationIndex);
        }

        private void button_frameDelete_Click(object sender, EventArgs e)
        {
            int index = int.Parse(textBox_frameIndex.Text);
            animationList[currentAnimationIndex].spriteList.RemoveAt(index);

            ChangeCurrentAnimation(currentAnimationIndex);
        }

        private void button_frameChange_Click(object sender, EventArgs e)
        {
            int index = int.Parse(textBox_frameIndex.Text);

            if (index >= animationList[currentAnimationIndex].spriteList.Count)
                return;

            animationList[currentAnimationIndex].spriteList[index].frameTime = float.Parse(textBox_selectFrameTime.Text);
            animationList[currentAnimationIndex].spriteList[index].eventStr = textBox_frameEvent.Text;

            ChangeCurrentAnimation(currentAnimationIndex);
        }

        private void saveAnimationsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < animationList.Count; i++)
            {
                string csv = string.Empty;

                csv += "index,imagePath,centerX,centerY,loop,frameTime,eventStr,width,height,offsetX,offsetY,";

                for (int j = 0; j < animationList[i].spriteList.Count; j++)
                {
                    csv += "\r\n";

                    csv += j.ToString();
                    csv += ",";
                    
                    csv += animationList[i].spriteList[j].fileName;
                    csv += ",";

                    csv += animationList[i].centerX;
                    csv += ",";

                    csv += animationList[i].centerY;
                    csv += ",";

                    csv += animationList[i].loop;
                    csv += ",";

                    if (animationList[i].spriteList[j].frameTime == 0)
                        csv += animationList[i].frameTime;
                    else
                        csv += animationList[i].spriteList[j].frameTime;

                    csv += ",";

                    csv += animationList[i].spriteList[j].eventStr;
                    csv += ",";

                    csv += animationList[i].spriteList[j].width.ToString();
                    csv += ",";

                    csv += animationList[i].spriteList[j].height.ToString();
                    csv += ",";

                    csv += animationList[i].spriteList[j].offsetX.ToString();
                    csv += ",";

                    csv += animationList[i].spriteList[j].offsetY.ToString();
                    csv += ",";
                }

                File.WriteAllText(currentFolderPath + '\\' + animationList[i].name + ".ani", csv);
            }
        }
    }
}
