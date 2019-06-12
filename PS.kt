fun main(args:Array<String>){with(java.util.Scanner(System.`in`)) {
  for(tc in 1..nextInt()) {
    val r=nextInt()
    val n=nextInt()
    val d=Array(n+1){Array(r+1){1}}
    for(i in 1..n) {
      for(j in 1..minOf(i,r)) {
        d[i][j]=d[i-1][j-1]+(if(j!=i) d[i-1][j] else 0)
      }
    }
    println(d[n][r])
  }
}}
