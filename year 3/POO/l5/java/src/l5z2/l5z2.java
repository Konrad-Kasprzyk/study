package l5z2;

import java.io.*;

public class l5z2 {
    public static void main(String[] args) throws IOException {
        FileInputStream sourceStream = new FileInputStream("file.txt");
        FileOutputStream targetStream = new FileOutputStream ("targetfile.txt");
        CaesarStreamRead caesarStreamRead = new CaesarStreamRead(sourceStream, 5);
        CaesarStreamWrite caesarStreamWrite = new CaesarStreamWrite(targetStream, 5);
        int temp;
        while ((temp = caesarStreamRead.read()) != -1) {
            caesarStreamWrite.write(temp);
        }

        caesarStreamRead.close();
        caesarStreamRead.close();
    }
}

class CaesarStreamRead extends InputStream{
    private FileInputStream stream;
    private int shift;
    public CaesarStreamRead(FileInputStream stream, int shift){
        this.stream = stream;
        this.shift = shift;
    }

    @Override
    public int read() throws IOException {
        int buff = stream.read();
        if (buff <= 0)
            return buff;
        else
            return buff + shift;
    }
}

class CaesarStreamWrite extends OutputStream{
    private FileOutputStream stream;
    private int shift;
    public CaesarStreamWrite(FileOutputStream stream, int shift){
        this.stream = stream;
        this.shift = shift;
    }

    @Override
    public void write(int buff) throws IOException {
        stream.write(buff - shift);
    }
}
