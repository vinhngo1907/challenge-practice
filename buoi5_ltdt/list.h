/* KHAI BAO VA DINH NGHIA CTDL DANH SACH */
#define MAX_ELEMENTS 100

typedef int ElementType;
typedef struct {
ElementType data[MAX_ELEMENTS];
	int size;
} List;
/* Tao danh sach rong */
void make_null(List* L) {
	L->size = 0;
}
/* Them mot phan tu vao cuoi danh sach */
void push_back(List* L, ElementType x) {
	L->data[L->size] = x;
	L->size++;
}

//	kiem tra danh sach rong
int empty(List* l){
	return l->size==0;
}

/* Lay phan tu tai vi tri i, phan tu bat dau o vi tri 1
*/
ElementType element_at(List* L, int i) {
	return L->data[i-1];
}
/* Tra ve so phan tu cua danh sach */
int count_list(List* L) {
	return L->size;
}

//	kiem tra mot gia tri co thuoc danh sach
int member(List* l, ElementType x){
	int i, len= l->size;
	for(i=1;i<=len;++i){
		if(x==element_at(l, i)) return 1;
	}
	return 0;
}

//	copy danh sach src vao danh sach des
void copy_list(List* src, List* des){
	des->size = src->size;
	int i;
	for(i=0;i<src->size;++i){
		des->data[i] = src->data[i];
	}
}

//	tim chi so cua phan tu lon nhat danh sach
int max_at(List* l){
	int i, idx, max= 0;
	
	for(i=0;i<l->size;++i){
		if(l->data[i] > max){
			max = l->data[i];
			idx = i+1;
		}
	}
	
	return idx;
}

//	xoa phan tu tai vi tri idx trong danh sach
void delete_at(List* l, int idx){
	if(idx > 0 && idx <= l->size){
		int i;
		for(i=idx-1;i<l->size - 1;++i){
			l->data[i] = l->data[i+1];
		}
		
		--(l->size);
	}
}
