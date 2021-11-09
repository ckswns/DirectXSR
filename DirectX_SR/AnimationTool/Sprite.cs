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
        public int maxWidth;
        public int maxHeight;
        public string fileName;
        public float frameTime = 0;
        public string eventStr = "";

        public Image image;

        public Sprite(int width, int height, int offsetX, int offsetY, int maxWidth, int maxHeight, Image image, string fileName)
        {
            this.width = width;
            this.height = height;
            this.offsetX = offsetX;
            this.offsetY = offsetY;
            this.maxWidth = maxWidth;
            this.maxHeight = maxHeight;
            this.image = image;
            this.fileName = fileName;
        }
    }
}
