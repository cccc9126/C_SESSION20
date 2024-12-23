


#include <stdio.h>
#include <string.h>

#define MAX_SP 100

typedef struct {
    char maSP[20];
    char tenSP[100];
    float giaNhap;
    float giaBan;
    int soLuong;
} SanPham;

SanPham danhSachSP[MAX_SP];
int soLuongSP = 0;
float doanhThu = 0.0;

void nhapSanPham() {
    char maSP[20], tenSP[100];
    float giaNhap, giaBan;
    int soLuong;
    
    printf("Nhap ma san pham: ");
    scanf("%s", maSP);
    
    printf("Nhap ten san pham: ");
    getchar();
    fgets(tenSP, sizeof(tenSP), stdin);
    tenSP[strcspn(tenSP, "\n")] = 0;

    printf("Nhap gia nhap: ");
    scanf("%f", &giaNhap);
    
    printf("Nhap gia ban: ");
    scanf("%f", &giaBan);
    
    printf("Nhap so luong: ");
    scanf("%d", &soLuong);

    int index = -1;
    for (int i = 0; i < soLuongSP; i++) {
        if (strcmp(danhSachSP[i].maSP, maSP) == 0) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        danhSachSP[index].soLuong += soLuong;
        printf("Sản phẩm đã tồn tại, số lượng được cập nhật.\n");
    } else {
        strcpy(danhSachSP[soLuongSP].maSP, maSP);
        strcpy(danhSachSP[soLuongSP].tenSP, tenSP);
        danhSachSP[soLuongSP].giaNhap = giaNhap;
        danhSachSP[soLuongSP].giaBan = giaBan;
        danhSachSP[soLuongSP].soLuong = soLuong;
        soLuongSP++;
        doanhThu -= giaNhap * soLuong;
    }
}

void hienThiDanhSach() {
    if (soLuongSP == 0) {
        printf("Danh sach san pham rong!\n");
        return;
    }
    printf("\n%-20s%-30s%-10s%-10s%-10s\n", "Mã Sản Phẩm", "Tên Sản Phẩm", "Giá Nhập", "Giá Bán", "Số Lượng");
    for (int i = 0; i < soLuongSP; i++) {
        printf("%-20s%-30s%-10.2f%-10.2f%-10d\n", danhSachSP[i].maSP, danhSachSP[i].tenSP, danhSachSP[i].giaNhap, danhSachSP[i].giaBan, danhSachSP[i].soLuong);
    }
}

void banSanPham() {
    char maSP[20];
    int soLuongBan;
    
    printf("Nhap ma san pham can ban: ");
    scanf("%s", maSP);
    printf("Nhap so luong can ban: ");
    scanf("%d", &soLuongBan);

    int index = -1;
    for (int i = 0; i < soLuongSP; i++) {
        if (strcmp(danhSachSP[i].maSP, maSP) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("San pham khong ton tai!\n");
        return;
    }

    if (danhSachSP[index].soLuong == 0) {
        printf("San pham da het hang!\n");
        return;
    }

    if (soLuongBan > danhSachSP[index].soLuong) {
        printf("Khong con du so luong san pham!\n");
        return;
    }

    danhSachSP[index].soLuong -= soLuongBan;
    doanhThu += soLuongBan * danhSachSP[index].giaBan;
    printf("Ban %d san pham %s thanh cong!\n", soLuongBan, danhSachSP[index].tenSP);
}

void hienThiDoanhThu() {
    printf("Doanh thu hien tai: %.2f\n", doanhThu);
}

void sapXepTheoGia() {
    int chon;
    printf("Chon cach sap xep:\n1. Gia ban tang\n2. Gia ban giam\nNhap lua chon: ");
    scanf("%d", &chon);

    if (chon == 1) {
        for (int i = 0; i < soLuongSP - 1; i++) {
            for (int j = i + 1; j < soLuongSP; j++) {
                if (danhSachSP[i].giaBan > danhSachSP[j].giaBan) {
                    SanPham temp = danhSachSP[i];
                    danhSachSP[i] = danhSachSP[j];
                    danhSachSP[j] = temp;
                }
            }
        }
    } else if (chon == 2) {
        for (int i = 0; i < soLuongSP - 1; i++) {
            for (int j = i + 1; j < soLuongSP; j++) {
                if (danhSachSP[i].giaBan < danhSachSP[j].giaBan) {
                    SanPham temp = danhSachSP[i];
                    danhSachSP[i] = danhSachSP[j];
                    danhSachSP[j] = temp;
                }
            }
        }
    }
}

void timKiemSanPham() {
    char maSP[20];
    printf("Nhap ma san pham can tim: ");
    scanf("%s", maSP);

    int index = -1;
    for (int i = 0; i < soLuongSP; i++) {
        if (strcmp(danhSachSP[i].maSP, maSP) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("San pham khong ton tai!\n");
    } else {
        printf("\n%-20s%-30s%-10s%-10s%-10s\n", "Mã Sản Phẩm", "Tên Sản Phẩm", "Giá Nhập", "Giá Bán", "Số Lượng");
        printf("%-20s%-30s%-10.2f%-10.2f%-10d\n", danhSachSP[index].maSP, danhSachSP[index].tenSP, danhSachSP[index].giaNhap, danhSachSP[index].giaBan, danhSachSP[index].soLuong);
    }
}

int main(int argc, const char * argv[]) {
    int luaChon;

    do {
        printf("\nMENU\n");
        printf("1. Nhap san pham\n");
        printf("2. Hien thi danh sach san pham\n");
        printf("3. Ban san pham\n");
        printf("4. Hien thi doanh thu\n");
        printf("5. Sap xep san pham theo gia\n");
        printf("6. Tim kiem san pham\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1:
                nhapSanPham();
                break;
            case 2:
                hienThiDanhSach();
                break;
            case 3:
                banSanPham();
                break;
            case 4:
                hienThiDoanhThu();
                break;
            case 5:
                sapXepTheoGia();
                break;
            case 6:
                timKiemSanPham();
                break;
            case 7:
                printf("Thoat chuong trinh!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (luaChon != 7);

    return 0;
}

