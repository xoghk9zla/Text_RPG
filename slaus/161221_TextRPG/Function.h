#pragma once

template <typename T>
void Safe_Delete(T Obj)
{
	if(NULL != Obj)
	{
		delete Obj;
		Obj = NULL;
	}
}