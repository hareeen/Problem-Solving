import java.util.*
import kotlin.math.max

fun main(args:Array<String>) {
  val sc=Scanner(System.`in`)
  val N=sc.nextInt()
  val arr=Array(N){sc.nextInt()}
  val dp=Array(N){Array(2){-99999999}}
  dp[0][0]=arr[0]
  for(i in 1 until N) {
    if(i>1) dp[i][0]=max(max(dp[i-2][0], dp[i-2][1]), 0)+arr[i]
    else dp[i][0]=arr[i]
    dp[i][1]=dp[i-1][0]+arr[i]
  }
  println(dp[N-1].max())
  return
}
