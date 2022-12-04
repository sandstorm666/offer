//正确版本
for(vector<int>::iterator iter = ivec.begin();
			iter != ivec.end(); //iter++
			){
			if((*iter) %2 == 0){
			//	int tmp = *iter;
				iter = ivec.erase(iter);
			//	--iter;
				continue;
			}
			iter++;
	}
/* erase后迭代器失效，所以需要控制迭代器的增长。
*/
//错误版本
for(vector<int>::iterator iter = ivec.begin();
			iter != ivec.end(); //iter++
			){
			if((*iter) %2 == 0){
				iter = ivec.erase(iter);
			--iter;
				continue;
			}
			iter++;
  /*当迭代器指向索引0时，被删除了，迭代器指向1，然后在指向0，但是此时的0已被删除。
  如果没有--iter，则erase后，迭代器又会自动增1，导致遗漏*/
