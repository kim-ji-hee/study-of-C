#pragma pack(push, 1)   //����ü�� 1����Ʈ ũ��� ����

typedef struct _BITMAPFILEHEADER    //BMP ��Ʈ�� ���� ��� ����ü
{
    unsigned short bfType;  //BMP ���� ���� �ѹ�
    unsigned int   bfSize;  //���� ũ��
    unsigned short bfReserved1; //����
    unsigned short bfReserved2; //����
    unsigned int   bf0ffBits;   //��Ʈ�� �������� ���� ��ġ
} BITMAPFILEHEADER;

typedef struct _BITMAPINFOHEADER  //BMP ��Ʈ�� ���� ��� ����ü(DIB���)
{
    unsigned int   biSize;      //���� ����ü�� ũ��
    int            biWidth;     //��Ʈ�� �̹����� ���� ũ��
    int            biHeight;    //��Ʈ�� �̹����� ���� ũ��
    unsigned short biPlanes;    //����ϴ� �������� ��
    unsigned short biBitCount;  //�ȼ� �ϳ��� ǥ���ϴ� ��Ʈ ��
    unsigned int   biCompression;   //������
    unsigned int   biSizeImage; //��Ʈ�� �̹����� �ȼ� ������ ũ��
    int            biXPelsPerMeter; //�׸��� ���� �ػ�(���ʹ� �ȼ�)
    int            biYPelsPerMeter; //�׸��� ���� �ػ�(���ʹ� �ȼ�)
    unsigned int   biClrUsed;   //���� ���̺��� ���� ���Ǵ� ���� ��
    unsigned int   biClrImportant;  //��Ʈ���� ǥ���ϴµ� �ʿ��� ���� �ε��� ��
} BITMAPINFOHEADER;

typedef struct _RGBTRIPLE
{
    unsigned char rgbtBlue;
    unsigned char rgbtGreen;
    unsigned char rgbtRed;
} RGBTRIPLE;

#pragma pack(pop)

#define PIXEL_SIZE  3
#define PIXEL_ALIGN 4

int main()
{
    FILE *fpBmp;    //��Ʈ�� ���� ������
    FILE *fpTxt;    //�ؽ�Ʈ ���� ������
    BITMAPFILEHEADER fileHeader;    //��Ʈ�� ���� ��� ����ü ����
    BITMAPINFOHEADER infoHeader;    //��Ʈ�� ���� ��� ����ü ����
    
    unsigned char *image;   //�ȼ� ������ ������
    int size;   //�ȼ� ������ ũ��
    int width, height;  //��Ʈ�� �̹����� ����, ���� ũ��
    int padding;    //�ȼ� �������� ���� ũ�Ⱑ 4�� ����� �ƴ� �� ���� ������ ũ��

    char ascii[] = {'#','#','@','%','=','+','*',':','-','.',' '};
    //11��, �� �ȼ��� ǥ���� ASCII ����. �ε����� �������� ������� ���� ǥ��

    fpBmp = fopen("Peppers80x80.bmp","rb"); //��Ʈ�� ������ ���̳ʸ� ���� ����
    if (fpBmp == NULL)  //���� ���⿡ �����ϸ�
        return 0;       //���α׷� ����

    if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fpBmp) < 1)
    {
        fclose(fpBmp);
        return 0;
        //��Ʈ�� ���� ��� �б�. �б⿡ �����ϸ� ���� �����͸� �ݰ� ���α׷� ����
    }

    if (fileHeader.bfType != 'MB')
    {
        fclose(fpBmp);
        return 0;
        //���� �ѹ��� MB�� �´��� Ȯ��(2����Ʈ ũ���� BM�� ��Ʋ ��������� �о����Ƿ� MB�� ��)
        //���� �ѹ��� ���� ������ ���α׷� ����
    }

    if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fpBmp) < 1)
    {
        fclose(fpBmp);
        return 0;
        //��Ʈ�� ���� ��� �б�. �б⿡ �����ϸ� ���� �����͸� �ݰ� ���α׷� ����
    }

    if (infoHeader.biBitCount !=24)
    {
        fclose(fpBmp);
        return 0;
        //24��Ʈ ��Ʈ���� �ƴϸ� ���α׷� ����
    }

    size = infoHeader.biSizeImage;  //�ȼ� ������ ũ��
    width = infoHeader.biWidth;     //��Ʈ�� �̹����� ���� ũ��
    height = infoHeader.biHeight;   //��Ʈ�� �̹����� ���� ũ��




}