# get_next_line - Satır Satır Dosya Okuma

## 📚 Proje Açıklaması

**get_next_line**, bir file descriptor'dan satır satır okuma yapan bir fonksiyon yazılmasını gerektiren eğitim projesidir. Bu proje, dosya I/O, buffer yönetimi, memory allocation ve string handling gibi kritik konuları öğretir.

## 🎯 İçeriği

### Fonksiyon Prototipi

```c
char *get_next_line(int fd);
```

**Davranış:**
- Verilen file descriptor'dan bir satırı okur
- Satırı dinamik olarak allocate edilen string olarak döndürür
- Newline karakteri (`\n`) dahil edilir
- Dosya sonuna ulaşıldığında NULL döndürür
- Hata durumunda NULL döndürür

## 🛠️ Öğrenilen Konseptler

### 1. File Descriptor (FD) Yönetimi
```c
int fd = open("file.txt", O_RDONLY);
char *line = get_next_line(fd);  // fd'den oku
close(fd);
```

### 2. Buffer Yönetimi
```c
#define BUFFER_SIZE 42  // Okuma buffer boyutu

// Her seferde BUFFER_SIZE kadar oku
char buffer[BUFFER_SIZE + 1];
read(fd, buffer, BUFFER_SIZE);
```

### 3. Static Variable Kullanımı
```c
static char *leftover = NULL;  // Seferler arasında veri saklama
```

Bir önceki okumada kalan veriler bir sonraki çağrı için saklanır.

### 4. String Manipülasyonu
```c
// Newline'ı bul
char *newline = ft_strchr(buffer, '\n');

// String birleştir
result = ft_strjoin(leftover, buffer);

// Substring oluştur
next_line = ft_substr(result, 0, newline - result + 1);
```

## 📖 Algoritma

```
1. Static buffer'dan leftover data al
2. Eğer newline yoksa:
   a. File'dan BUFFER_SIZE kadar oku
   b. Buffer'a ekle
   c. Newline kontrol et
   d. Tekrar 2a'ya git
3. Newline bulundu:
   a. Newline'a kadar kısmı line olarak ayır
   b. Kalanını static buffer'da sakla
   c. Line'ı döndür
```

## 💡 Kullanım Örneği

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);  // Line'da \n zaten var
        free(line);
    }
    
    close(fd);
    return 0;
}
```

## 🛠️ Derleme

```c
// Derleme örneği (library olarak değil, main.c'ye dahil edilir):
gcc -D BUFFER_SIZE=42 -o read file.c get_next_line.c get_next_line_utils.c

// Buffer size değiştirilebilir:
gcc -D BUFFER_SIZE=1 -o read file.c get_next_line.c get_next_line_utils.c
gcc -D BUFFER_SIZE=10000 -o read file.c get_next_line.c get_next_line_utils.c
```

## 📚 Öğrenme Çıktıları

✅ File descriptor'lar anlaşıldı  
✅ Buffer yönetimi mastered  
✅ Static variable kullanımı öğrenildi  
✅ String manipülasyonu pratiği yapıldı  
✅ Memory allocation/deallocation öğrenildi  
✅ Edge cases (EOF, errors) işlendi  

## 🔧 Dosya Yapısı

```
get_next_line/
├── get_next_line.c         # Main function
├── get_next_line_utils.c   # Helper functions
└── get_next_line.h         # Header
```

## 📝 Önemli Notlar

### Multiple File Descriptor Desteği

```c
// Aynı anda farklı dosyalardan okuyabilir
int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);

char *line1 = get_next_line(fd1);  // file1'den oku
char *line2 = get_next_line(fd2);  // file2'den oku
char *line3 = get_next_line(fd1);  // file1'den devam et
```

### Buffer Size Değişkenliği

```bash
# Minimum buffer size (1)
gcc -D BUFFER_SIZE=1 ...

# Normal buffer size
gcc -D BUFFER_SIZE=42 ...

# Büyük buffer size
gcc -D BUFFER_SIZE=5000 ...
```

### Newline Davranışı

```
Dosya içeriği:
"Hello\nWorld\nTest"

get_next_line(fd) -> "Hello\n"
get_next_line(fd) -> "World\n"
get_next_line(fd) -> "Test"     (no \n)
get_next_line(fd) -> NULL       (EOF)
```

## 🎯 Teknik Zorluklar

### 1. Static Variable State Management

```c
static char *leftover = NULL;

// Problem: Üst üste çağrılar arasında state saklama
// Çözüm: Dinamik olarak satır satır oku ve sakla
```

### 2. Dinamik Buffer Yönetimi

```c
// Satırın ne kadar uzun olacağı bilinmiyor
// Çözüm: String birleştirerek büyütmek
result = ft_strjoin(leftover, buffer);
```

### 3. Multiple FD'ler

```c
// get_next_line(fd1) ve get_next_line(fd2) sırayla çağrılabilir
// Her FD'nin kendi state'i olmalı
// Çözüm: Bağlantılı liste veya static array kullanarak

// Örnek: Her FD için ayrı buffer
static char *leftover[4096] = {NULL};  // FD 0-4095 için
```

## 🚀 İleri Uygulamalar

### Geri Okuma (Seeker'ı olmayan pipe'lardan)
```c
// Pipe'lar seekable değildir, sadece forward okuma yapılabilir
// get_next_line ile pipe'ı satır satır okuyabiliriz
```

### Test Yöntemleri

```bash
# Küçük buffer size ile test
./program < large_file.txt

# Tek karakter buffer size ile test
gcc -D BUFFER_SIZE=1 -o program ...
./program < large_file.txt

# Çok büyük buffer size ile test
gcc -D BUFFER_SIZE=100000 -o program ...
./program < large_file.txt
```

## 📚 Norm Standartları

- 80 karaktere kadar satır uzunluğu
- Fonksiyon başına maksimum 25 satır
- 4 karakterlik indentation
- Memory leaks yoktur
- Norm compliance sağlanmıştır (42 okulu)

## 💡 Key Learning Points

1. **I/O Efficiency**: Buffer kullanarak sistem çağrılarını minimize etme
2. **Memory Management**: Dinamik allocation ve proper cleanup
3. **State Management**: Static variable'lar ile state saklama
4. **Edge Cases**: EOF, empty lines, no newline at EOF gibi durumlar
5. **Performance**: Buffer size ile performans optimizasyonu

Bu proje, sistem programlaması ve dosya I/O konularını derinlemesine öğretir.
