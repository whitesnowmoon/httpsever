
// 下拉菜单
$(function () {
    var nav = document.querySelector('.hr-nav');
    // 拿到四个小li 我在a用hover 一离开a就没有了，用在li
    //  是包括了ul下面的，就可以移动到下面  
    var lis = nav.children;
    for (var i = 0; i < lis.length; i++) {
        //    循环注册
        lis[i].onmouseenter = function () {
            // this.children[2].slideDown(300);不知道为什么这种写法不行
            // lis[i].onmouseover=function(){
            //     this.children[2].style.display='block';

            $(this).find('.sub_muse').stop().slideDown(300);
        }
        lis[i].onmouseleave = function () {
            $(this).find('.sub_muse').stop().slideUp(200);
            // this.children[2].style.display='none';
        }


    }
})

/*
/
$('#flip').mouseleave(function(){

$(this).find('#panel').slideUp(300);

})
    $('#flip').mouseover(function(){

$( '#panel').slideDown(300);

})
/

*/
//下拉菜单的另一种写法
/*
$(function(){
   var nav=document.querySelector('.hr-nav');
   var lis=nav.children;//lis装着nav的亲儿子
   for(var i=0;i<2;i++){
//    循环注册
       lis[i].mouseover(function(){
          $(this).find('.sub_muse').slideDown('slow');
           console.log('onmoseover');console.log(this.children[2]);
           // $("#panel").slideUp("slow");
       })
       lis[i].mouseleave(function(){
           console.log('onmoseout');
           $(this).find('.sub_muse').slideUp('slow');
       })
   }
})
*/

// 鼠标放上去出现就出现小二维码的函数，参数是索引
$(function () {
    var index = 0;
    var f;
    function change_color(num) {
        $('.button').css('background-color', '#cccccc')
        $('.button').eq(num).css('background-color', '#1e824a')
    }
    function change(num) {
        $('.img').css('opacity', '0');
        $('.img').eq(num).css('opacity', '1');
        change_color(num);
    
    }

    // 设置定时器

    function dsqhs() {
        f = setInterval(function () {
            if (index >= 2) index = -1;
            index++;
            // 改变图片
            change(index);
        }, 5000)
    }
    dsqhs();

    //  $('.box').mouseenter(function(){
    //     clearInterval(f);
    //     console.log('tzl');
    //   })
    // $('.box').mouseleave(dsqhs);

    $('.box').mouseenter(function () {
        clearInterval(f);
        
    })
    $('.box').mouseleave(dsqhs);

    $('.left').click(function () {
        if (index <= 0) index = $('.img').length;
        console.log(index);
        index--;
        console.log(index);
        change(index);
    })

    $('.right').click(function () {
        if (index >= $('.img').length - 1) index = -1;
        index++;
        change(index);
    })
    $('.button').click(function () {
        var numt = $(this).index();
        change(numt);
    })
})

// 轮播图改变图片时，小圆圈+图片 的改变
$(function () {
    var index = 0;
    var f;
    function change_color(num) {
        $('.button02').css('background-color', '#cccccc')
        $('.button02').eq(num).css('background-color', '#1e824a')
    }
    function change(num) {
        $('.img02').css('opacity', '0');
        $('.img02').eq(num).css('opacity', '1');
        change_color(num);
    }

    // 设置定时器
    function dsqhs() {
        f = setInterval(function () {
            if (index >= 5) index = -1;
            index++;
            // 改变图片
            change(index);
        }, 3000)
    }
    dsqhs();


    // 鼠标进来，轮播图就停止，离开再次调用定时器
    $('.box02').mouseenter(function () {
        clearInterval(f);
     })
    $('.box02').mouseleave(dsqhs);

    //  点击小圆圈 index（）索引，change图片
    $('.button02').click(function () {
        var numt = $(this).index();
        change(numt);
    })
})

// 根据图片100%在屏幕的宽度动态改变高度
// $(function () {
//     var h = $('.img').height();
//     console.log('轮播图高度'+h);
//     $('.box').height(h);
// })

// 改变footer 小图 二维码的函数,并且调用
$(function () {
    function change_logo(nth) {
        $('.share_logo').eq(nth).mouseenter(function () {
            $('.small-p').eq(nth).css('display', 'block');
        })
        $('.share_logo').eq(nth).mouseleave(function () {
            $('.small-p').eq(nth).css('display', 'none');
        })
    }
    $('.li').mouseenter(function () {
        var numt = $(this).index();
        console.log(numt);
        change_logo(numt);
    })

})

//  左右联动开关
$(function () {
    $('#main1_sw').find('.tt-1').mouseenter(function () {
        //找到main1（第一个内容）的tt标题的 左边那个
        $('#main1_sw').find('.tt-2').css({ 'color': '#a9a9a9', 'border-bottom-color': '#fff' })//鼠标到左边那个小标题，右边就变
        $(this).css({ 'color': '#2F2F2F', 'border-bottom-color': '#f7d66b' })
        $('.m3_news_r').hide();
        $('.m3_news_l').show();
    })

    $('#main1_sw').find('.tt-2').mouseenter(function () {
        console.log('main1_sw');
        $('#main1_sw').find('.tt-1').css({ 'color': '#a9a9a9', 'border-bottom-color': '#fff' })
        $(this).css({ 'color': '#2F2F2F', 'border-bottom-color': '#f7d66b' })
        $('.m3_news_l').stop().hide();
        $('.m3_news_r').stop().show();
    })
    // $('#main1_sw').find('.tt-2').style.css({'color':'#2F2F2F','border-bottom-color':'#f7d66b'})
})
$(function () {
    // main3 内容3 m1 面板1
    $('#main3_sw').find('.tt-1').mouseenter(function () {
        $('#main3_sw').find('.tt-2').css({ 'color': '#a9a9a9', 'border-bottom-color': '#fff' })
        $(this).css({ 'color': '#2F2F2F', 'border-bottom-color': '#f7d66b' })
        $('.m1_news_r').hide();
        $('.m1_news_l').show();
    })

    $('#main3_sw').find('.tt-2').mouseenter(function () {
        // console.log('main1_sw');
        $('#main3_sw').find('.tt-1').css({ 'color': '#a9a9a9', 'border-bottom-color': '#fff' })
        $(this).css({ 'color': '#2F2F2F', 'border-bottom-color': '#f7d66b' })
        $('.m1_news_l').hide();
        $('.m1_news_r').show();
    })
    // $('#main1_sw').find('.tt-2').style.css({'color':'#2F2F2F','border-bottom-color':'#f7d66b'})
})
$(function () {
    $('#i2').mouseenter(function () {
        $(this).find('.foot_sub_muse').stop().show();
    })
    $('#i2').mouseleave(function () {
        $(this).find('.foot_sub_muse').stop().slideUp(200);
    })
})
$(function () {
    var num = 0, i = 0;
    $('.bt1').click(function () {
        num -= 320; i++;
        var nav = document.querySelector('.slick_track ');
        var lis = nav.children;//lis装着nav的亲儿子
        $('.slick_track').css({ 'transform': 'translate3d(' + num + 'px,0,0)' })
        $(lis).css({ 'visibility': 'hidden' });
        $(lis[i]).css({ 'visibility': 'visible' });
        console.log(lis[i]);
        console.log(i);
    })
    $('.bt2').click(function () {
        var nav = document.querySelector('.slick_track ');
        var lis = nav.children;//lis装着nav的亲儿子
        num += 320;
        i--;
        $('.slick_track').css({ 'transform': 'translate3d(' + num + 'px,0,0)' })
        //  $(lis).css({'visibility':'hidden'});
        // $(lis[i]). css({'visibility':'visible'});
        // console.log(lis[i]);
        // console.log(i);
    })

})

// 内容3的轮播图
$(function () {

    var num = 0, i = 0, n = 0, pd = 0;
    var index = 0;
    var f;
    function change_color(num) {
        $('.slick_bt').css('background-color', '#cccccc')
        $('.slick_bt').eq(num).css('background-color', '#1e824a')
    }
    function change(n) {
        var nav = document.querySelector('.slick_track');
        var lis = nav.children;//lis装着nav的亲儿子
        $('.slick_track').css({ 'transform': 'translate3d(' + n + 'px,0,0)' })
        // $(lis).css({'visibility':'hidden'});
        // $(lis[abs(n/320)]). css({'visibility':'visible'});
    }
    // 往前走
    function pre(numt) {
        change(-numt * 320);
        change_color(numt);
    }
    // function hou(numt){
    //     change(numt*320);
    // }
    // -960就-640就可以了，因为循环且都是负数，故写一个函数就可以了



    // 设置定时器

    function dsqhs() {
        f = setInterval(function () {
            if (pd == 0) {
                index++;
                pre(index);
                // 看了第三张
                if (index == 3) pd = 1;
            }
            else if (pd == 1) {
                index--;
                pre(index);
                if (index == 0) pd = 0;
            }

            // 改变图片

        }, 3000)
    }
    dsqhs();

    $('.slick_track').mouseover(function () {
        clearInterval(f);
    })
    $('.slick_track').mouseleave(dsqhs);


    $('.slick_bt').click(function () {
        var numt = $(this).index();
        pre(numt);
    })
})

// 校报
$(function () {
    var num = 1;
    function change1(num) {
        // var ch=document.querySelector('.xiaobao').children;

        if (num == 1) {

              $('.txt').text(' 当前 608期');
            $('.control .shang').removeClass('xianshi');
            $('.control .pre').addClass('xianshi');
        }

        else if (num == 2) {
            
            $('.news1').removeClass('baof')
            $('.news2').removeClass('baol')
            $('.news3').removeClass('baoh')
            $('.news4').removeClass('baor')
             
            $('.news1').addClass('baol')
            $('.news2').addClass('baoh')
            $('.news3').addClass('baor')
            $('.news4').addClass('baof')
            $('.txt').text(' 当前 609期');
        }

        else if (num == 3) {

            $('.news1').removeClass('baol')
            $('.news2').removeClass('baoh')
            $('.news3').removeClass('baor')
            $('.news4').removeClass('baof')
            
            

            $('.news1').addClass('baoh')
            $('.news2').addClass('baor')
            $('.news3').addClass('baof')
            $('.news4').addClass('baol')
            $('.txt').text(' 当前 610期');
        }

        else if (num == 4) {
            
            $('.news1').removeClass('baoh')
            $('.news2').removeClass('baor')
            $('.news3').removeClass('baof')
            $('.news4').removeClass('baol')

            $('.news1').addClass('baor')
            $('.news2').addClass('baof')
            $('.news3').addClass('baol')
            $('.news4').addClass('baoh')
            $('.txt').text(' 当前 611期');
            $('.control .pre').removeClass('  xianshi');
            $('.control .shang').addClass('  xianshi');
        }

    }
    function change2(num) {
        // var ch=document.querySelector('.xiaobao').children;

        if (num == 1) {

            $('.news1').removeClass('baol')
            $('.news2').removeClass('baoh')
            $('.news3').removeClass('baor')
            $('.news4').removeClass('baof')

          

            $('.news1').addClass('baof')
            $('.news2').addClass('baol')
            $('.news3').addClass('baoh')
            $('.news4').addClass('baor')
             
            
            $('.txt').text(' 当前 608期');
            $('.control .shang').removeClass('xianshi');

            $('.control .pre').addClass('xianshi');
        }

        else if (num == 2) {
            $('.news1').removeClass('baoh')
            $('.news2').removeClass('baor')
            $('.news3').removeClass('baof')
            $('.news4').removeClass('baol')
            
          

            $('.news1').addClass('baol')
            $('.news2').addClass('baoh')
            $('.news3').addClass('baor')
            $('.news4').addClass('baof')
            $('.txt').text(' 当前 609期');
        }

        else if (num == 3) {

            $('.news1').removeClass('baor')
            $('.news2').removeClass('baof')
            $('.news3').removeClass('baol')
            $('.news4').removeClass('baoh')
            
           

            $('.news1').addClass('baoh')
            $('.news2').addClass('baor')
            $('.news3').addClass('baof')
            $('.news4').addClass('baol')
            $('.txt').text(' 当前 610期');
        }

        else if (num == 4) {
            
            $('.news1').removeClass('baoh')
            $('.news2').removeClass('baol')
            $('.news3').removeClass('baof')
            $('.news4').removeClass('baor')

            $('.news1').addClass('baor')
            $('.news2').addClass('baoh')
            $('.news3').addClass('baol')
            $('.news4').addClass('baof')
            $('.txt').text(' 当前 611期');
            $('.control .pre').removeClass('  xianshi');
           $('.control .shang').addClass('  xianshi');
        }

    }


    
    $('.shang').click(function () {
        if (num > 1) {
            num--;
            change2(num);
       console.log(num);
        }

    })

    $('.pre').click(function () {
        if (num <4) {
            num++;
            change1(num);
            console.log(num);
        }

    })


})

// 搜索框点击事件
$(function(){
    var pd=0;
   
    $('.search').click(function(){
        //  自动获取焦点
      $('.search-title').css({'width':'200px'});
      $(".search-title").focus();
  }) 
  $(".search-title").blur(function(){
    $('.search-title').css({'width':'35px'});
  });
      
})

// 返回小图标
$(function(){
    $("#my").click(function(){ 
         var y=document.documentElement.scrollTop;
         var mytimer=setInterval(function(){
            y-=(document.documentElement.scrollTop/10);
       document.documentElement.scrollTop=y;
if(y<=0)clearInterval(mytimer);
        },50)
          })
    window.onscroll=function(){
        if(document.documentElement.scrollTop>300){
$('#my').show();
        }
        if(document.documentElement.scrollTop<300){
$('#my').hide();
        }
        
    }
})