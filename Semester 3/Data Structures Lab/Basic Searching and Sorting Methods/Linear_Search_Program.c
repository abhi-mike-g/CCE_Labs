#include <stdio.h>
int main(){
  int a[100], n, key;
  printf("Enter Array Size: ");
  scanf("%d", &n);
  for(int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  printf("Enter Search Element: ");
  scanf("%d", &key);
  for(int i = 0; i < n; i++)
    if(a[i] == key)
      printf("%d found in position %d", key, i);
    else
      printf("Element does not exist");
  return 0;
}
