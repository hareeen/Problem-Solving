fun main(args:Array<String>){with(java.util.Scanner(System.`in`)) {
  val n=nextInt()
  val r=nextInt()
  val d=Array(n+1){Array(r+1){1}}
  for(i in 1..n) {
    for(j in 1..minOf(i,r)) {
      d[i][j]=(d[i-1][j-1]+(if(j!=i) d[i-1][j] else 0))%10007
    }
  }
  println(d[n][r])
}}
