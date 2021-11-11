using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace NPK_AnimationTool
{
    class Sprite
    {
        public int width;
        public int height;
        public int offsetX;
        public int offsetY;
        public string fileName;
        public float frameTime = 0;
        public string eventStr = "";

        public Image image;

        public Sprite(Image image, string fileName)
        {
            this.width = image.Width;
            this.height = image.Height;
            this.offsetX = 0;
            this.offsetY = 0;
            this.image = image;
            this.fileName = fileName;
        }
    }
}
