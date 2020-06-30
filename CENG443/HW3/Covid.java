
import java.util.*;
import java.util.Comparator;
import java.util.Optional;
import java.util.stream.Collectors;
import java.nio.file.Paths;
import java.nio.file.Files;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.stream.IntStream;

public class Covid
{
    // You can add your own variables between them.

    // You can add your own variables between them.

    // You must not change between them.
    private List<List<String>> rows;
    // Constructor reads the ”covid19.csv” file line by line and write it to ”rows” variable in this format
    // [[”ABW”, ”Aruba”, ”2020-03-13”,”2”, ”2”, ”0”, ”0”], [”ABW”, ”Aruba”, ”2020-03-20”, ”4”, ”2”, ”0”, ”0”], ...,
    // [”ZWE”, ”Zimbabwe”, ”2020-04-26”,”31”, ”2”, ”4”, ”0”], [”ZWE”, ”Zimbabwe”, ”2020-04-27”, ”31”, ”0”, ”4”, ”0”]].
    public Covid()
    {
        try
        {
            this.rows = Files
                    .lines(Paths.get("/home/ali/Downloads/2019-2020 2. DÖNEM/CENG443/HWS/HW3"))
                    .map(row -> Arrays.asList(row.split(",")))
                    .collect(Collectors.toList());
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }
    // You must not change between them.
    //”System.out.printf()” method while printing to screen
    public void printOnlyCases(String location, String date)
    {
        rows.forEach(el->{if(el.get(1).equals(location) && el.get(2).equals(date))
            System.out.printf("Result %d", Integer.parseInt(el.get(3)) - Integer.parseInt( el.get(5)) ); });
    }

    public long getDateCount(String location)
    {
        long toReturn = 0;
        toReturn = rows.stream().filter(el -> el.get(1).equals(location)).count();
        return toReturn;
    }

    public int getCaseSum(String date)
    {
        int toReturn = 0;
        toReturn = rows.stream().filter(el->el.get(2).equals(date)).mapToInt(i->Integer.parseInt(i.get(4))).sum();
        return toReturn;
    }

    public long getZeroRowsCount(String location)
    {
        long toReturn = rows.stream().filter(el -> el.get(1).equals(location) && (Integer.parseInt(el.get(6)) == 0 &&
                Integer.parseInt(el.get(5)) == 0 &&
                Integer.parseInt(el.get(4)) == 0 && Integer.parseInt(el.get(3)) == 0)).count();
        return toReturn;
    }

    public double getAverageDeath(String location)
    {
        double toReturn = 0;
        int rowCount = (int) rows.stream().filter(el -> el.get(1).equals(location)).count();
        List<List<String>> innerList =rows.stream().filter(el->el.get(1).equals(location) ).collect(Collectors.toList());
        int totaldeath = Integer.parseInt(innerList.get(rowCount-1).get(5));

        if(rowCount!=0) toReturn = totaldeath/(double)rowCount;
        toReturn = Double.parseDouble(new DecimalFormat("##.00").format(toReturn));
        return toReturn;
    }

    public String getFirstDeathDayInFirstTenRows(String location)
    {
        String toReturn = null;

        List<String> date;
        List<List<String>> innerList =rows.stream().filter(el->el.get(1).equals(location) ).limit(10).collect(Collectors.toList());
        date = innerList.stream().filter(el->Integer.parseInt(el.get(6)) != 0).findFirst().orElse(Collections.singletonList("Not Found"));
        if(date.get(0).equals("Not Found")) toReturn = "Not Found";
        else toReturn = date.get(2);

        return toReturn;
    }

    public String[] getDateCountOfAllLocations()
    {
        String[] toReturn = null;
        List<String> locCodes =rows.stream().map(e-> e.get(0) ).distinct().collect(Collectors.toList());
        List<String> locations = rows.stream().map(e-> e.get(1)).distinct().collect(Collectors.toList());
        List<List<String>> merged = IntStream.range(0,locations.size()).mapToObj(i-> Arrays.asList((String) locations.get(i),locCodes.get(i))).collect(Collectors.toList());
        toReturn = merged.stream().map(e-> e.get(1) + ": " +getDateCount(e.get(0))).distinct().toArray(String[]::new);
        //toReturn = rows.stream().map(e-> e.get(0) + ": " +getDateCount(e.get(1))).distinct().toArray(String[]::new);
/*
        for (String s: toReturn
             ) {
            System.out.println(s);
        }*/
        return toReturn;
    }

    public List<String> getLocationsFirstDeathDay()
    {
        List<String> toReturn = null;
        List<List<String>> innerList =rows.stream().filter(el->el.get(5).equals(el.get(6)) && !el.get(5).equals("0")).collect(Collectors.toList());
        toReturn = innerList.stream().map(e->e.get(1) + ": " + e.get(2)).collect(Collectors.toList());

        return toReturn;
    }

    public String trimAndGetMax(String location, int trimCount)
    {
        String toReturn = null;
        List<List<String>> innerList =rows.stream().filter(el->el.get(1).equals(location) ).collect(Collectors.toList());
        List<List<String>> sr = innerList.stream().sorted(Comparator.comparingInt(anInt -> Integer.parseInt(anInt.get(4)))).collect(Collectors.toList());
        //List<List<String>> sr = innerList.stream().max((int1,int2) -> Integer.compare(Integer.parseInt(int1.get(4)),Integer.parseInt(int2.get(4))));
        long length = getDateCount(location);
        sr = sr.stream().limit(length-trimCount).collect(Collectors.toList());
        sr = sr.stream().skip(trimCount).collect(Collectors.toList());
        Optional<List<String>> op = sr.stream().max(Comparator.comparingInt(anInt -> Integer.parseInt(anInt.get(6))));
        toReturn = op.get().get(2) + ": " + op.get().get(6);
        //System.out.println("toreturn "+ toReturn);
/*
        for (List<String> s:sr
             ) {
            System.out.println(s);
        }
*/
        return toReturn;
    }

    public List<List<String>> getOnlyCaseUpDays(String location)
    {
        List<List<String>> toReturn = null;
        List<List<String>> innerList =rows.stream().filter(el->el.get(1).equals(location) ).collect(Collectors.toList());
        toReturn = innerList.stream().filter(el->Integer.parseInt(el.get(4)) != 0).collect(Collectors.toList());

        return toReturn;
    }

    public static void main(String[] args)
    {
        Covid c = new Covid();
        c.printOnlyCases("Turkey", "2020-03-20");
        System.out.println();
        c.printOnlyCases("United States", "2020-02-25");
        System.out.println();
        long b = c.getDateCount("Turkey");
        System.out.println(b);
        long bb = c.getDateCount("Italy");
        System.out.println(bb);
        System.out.println();
        int d = c.getCaseSum("2020-04-05");
        System.out.println(d);
        long dd = c.getZeroRowsCount("Australia");
        System.out.println(dd);
        long ddd = c.getZeroRowsCount("Turkey");
        System.out.println(ddd);

        double avg = c.getAverageDeath("Italy");
        System.out.println(avg);
        String str = c.getFirstDeathDayInFirstTenRows("Italy");
        System.out.println(str);
        String st1r = c.getFirstDeathDayInFirstTenRows("Turkey");
        System.out.println(st1r);
        c.getDateCountOfAllLocations();
        c.getLocationsFirstDeathDay();
        c.trimAndGetMax("Turkey",20);
        c.getOnlyCaseUpDays("Aruba");
    }
}
