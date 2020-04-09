from PIL import Image
import matplotlib.pyplot as plt  


def get_bit(number, shift = 0):
    """ zwraca int mający wartość 0 lub 1"""
    number = number >> shift
    bit = 1 & number
    return bit


def set_bit(number, shift = 0, bit = 1):
    """ zwraca int ze zmienionym bitem na pozycji shift """
    return (number & (~(1 << shift))) | (bit << shift) 


def hide(filename, message):
    """ zamienia wiadomość 'message' na listę bajtów, koduje 1 bit z tej listy w każym pikselu obrazka, 
        pierwsze 4 zakodowane bajty w obrazku stanowią liczbę zakodowanych bajtów na wiadomość 
        zwraca obrazek z zakodowaną wiadomością """
    img = Image.open(filename)
    pixels = img.getdata()
    curr_bit = 0
    curr_byte = 0

    bit = 0

    bytes_arr = bytearray(message, 'utf-8')
    bytes_encoded = len(bytes_arr)
    
    newPixels= []

    for i in range(32):
        red, green, blue, alpha = pixels[i]
        bit = get_bit( bytes_encoded, curr_bit )
        red = red | bit
        curr_bit += 1

        newPixels.append( (red, green, blue, alpha) )

    curr_bit = 0

    for i in range(32,len(pixels)):
        red, green, blue, alpha = pixels[i]

        if curr_byte < bytes_encoded:
            bit = get_bit( bytes_arr[curr_byte], curr_bit )
            red = set_bit(red, 0, bit)

            if curr_bit == 7:
                curr_bit = 0
                curr_byte += 1
            else:
                curr_bit += 1

        newPixels.append( (red, green, blue, alpha) )
    
    img.putdata(newPixels)
    return img


def retr(img):
    pixels = img.getdata()
    curr_bit = 0
    curr_byte = 0
    bytes_encoded = 0

    for i in range(32):
        red, green, blue, alpha = pixels[i]
        bit = get_bit(red, 0)
        bytes_encoded = set_bit( bytes_encoded, curr_bit, bit )
        curr_bit += 1

    curr_bit = 0  
    bytes_array = bytearray(bytes_encoded)

    for i in range(32,len(pixels)):
        red, green, blue, alpha = pixels[i]

        if curr_byte < bytes_encoded:
            bit = get_bit( red, 0 )
            
            bytes_array[curr_byte] = set_bit(bytes_array[curr_byte], curr_bit, bit)
            if curr_bit == 7:
                curr_bit = 0
                curr_byte += 1
            else:
                curr_bit += 1

    message = str(bytes_array, 'utf-8')
    return message


def encode(message):
    msg1 = ""
    msg2 = ""
    for i in range(len(message)):
        if i % 2 == 0:
            msg1 += message[i]
        else:
            msg2 += message[i]
    return (msg1, msg2)


def decode(msg1,msg2):
    message = ""
    length = len(msg1) + len(msg2)
    for i in range(length):
        if i % 2 == 0:
            message += msg1[i//2]
        else:
            message += msg2[i//2]
    return message


def main():
    message = 'In the previous sections we have explained how paging works and have given a'\
    'few of the basic page replacement algorithms. But knowing the bare mechanics is '\
    'not enough. To design a system and make it work well you have to know a lot '\
    'more. It is like the difference between knowing how to move the rook, knight, '\
    'bishop, and other pieces in chess, and being a good player. In the following'\
    'sections, we will look at other issues that operating system designers must consider '\
    'carefully in order to get good performance from a paging system.'

    image = "test.png"

#    print("Oryginalna wiadomość przed steganografią:",message)
    msg1, msg2 = encode(message)
#    print("wiadomość przed umieszczeniem w obrazku nr 1 : ",msg1)
#    print("wiadomość przed umieszczeniem w obrazku nr 2 : ",msg2)

    img1 = hide(image,msg1)
    img2 = hide(image,msg2)

    msg1 = retr(img1)
    msg2 = retr(img2)
#    print("wiadomość z obrazka nr 1: ",msg1)
#    print("wiadomość z obrazka nr 2: ",msg2)

    message = decode(msg1,msg2)
    print("Oryginalna wiadomość po steganografii:",message)

    fig, axs = plt.subplots(3)

    oryginal_img = Image.open(image)
    axs[0].imshow(oryginal_img)
    axs[1].imshow(img1)
    axs[2].imshow(img2)

    axs[0].set(ylabel = 'oryginalny')
    axs[1].set(ylabel = 'zakodowany 1')
    axs[2].set(ylabel = 'zakodowany 2')

    plt.show()


if __name__ == '__main__': 
    main()












