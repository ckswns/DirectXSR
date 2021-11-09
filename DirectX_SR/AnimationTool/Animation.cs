using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NPK_AnimationTool
{
    class Animation
    {
        public List<Sprite> spriteList;
        public bool loop;

        public int centerX;
        public int centerY;

        public int currentFrame = 0;
        public float frameTime = 0;
        public string name;

        public Animation(ref List<Sprite> spriteList, string name, bool loop, int centerX, int centerY, float frameTime, int startFrame, int endFrame)
        {
            this.spriteList = new List<Sprite>(spriteList.GetRange(startFrame, endFrame - startFrame + 1));
            this.loop = loop;

            this.centerX = centerX;
            this.centerY = centerY;
            this.frameTime = frameTime;
            this.name = name;
        }

        public void Render()
        {
            Form1.myBuffer.Graphics.DrawRectangle(Form1.redPen, spriteList[currentFrame].offsetX, spriteList[currentFrame].offsetY, spriteList[currentFrame].width, spriteList[currentFrame].height);
            Form1.myBuffer.Graphics.DrawImage(spriteList[currentFrame].image, spriteList[currentFrame].offsetX, spriteList[currentFrame].offsetY, spriteList[currentFrame].width, spriteList[currentFrame].height);

            Form1.animationTimer.Interval = (int)(frameTime * 1000);
            if (spriteList[currentFrame].frameTime != 0 &&
                spriteList[currentFrame].frameTime != Form1.animationTimer.Interval)
            {
                Form1.animationTimer.Interval = (int)(spriteList[currentFrame].frameTime * 1000);
            }

            currentFrame++;
            if (currentFrame >= spriteList.Count)
            {
                currentFrame = 0;
                if(!loop)
                {
                    Form1.animationTimer.Stop();
                }
            }
        }

        public void Render(int frame)
        {
            if (frame >= spriteList.Count)
                return;

            currentFrame = frame;

            Form1.myBuffer.Graphics.DrawRectangle(Form1.redPen, spriteList[currentFrame].offsetX, spriteList[currentFrame].offsetY, spriteList[currentFrame].width, spriteList[currentFrame].height);
            Form1.myBuffer.Graphics.DrawImage(spriteList[currentFrame].image, spriteList[currentFrame].offsetX, spriteList[currentFrame].offsetY, spriteList[currentFrame].width, spriteList[currentFrame].height);

            currentFrame = frame;
            Form1.myBuffer.Graphics.DrawImage(spriteList[currentFrame].image, spriteList[currentFrame].offsetX, spriteList[currentFrame].offsetY, spriteList[currentFrame].width, spriteList[currentFrame].height);
        }
    }
}
