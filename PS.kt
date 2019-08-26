fun main(args:Array<String>) = with(java.util.Scanner(System.`in`)) {
  val N=nextInt()
  val S=nextInt()
  val arr=Array(N){nextInt()}

  var ans=0
  for(i in 1 until (1 shl N)) {
    var _s=0
    var idx=0
    var bits=i
    while(bits!=0) {
      if(bits%2==1) _s+=arr[idx]
      idx++
      bits/=2
    }
    if(_s==S) ans++;
  }

  println(ans)
}
